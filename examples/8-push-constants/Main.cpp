/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/BackendTraits.h>
#include <orhi/CommandBuffer.h>
#include <orhi/CommandPool.h>
#include <orhi/except/OutOfDateSwapChain.h>
#include <orhi/Fence.h>
#include <orhi/Framebuffer.h>
#include <orhi/Pipeline.h>
#include <orhi/PipelineLayout.h>
#include <orhi/Instance.h>
#include <orhi/Queue.h>
#include <orhi/RenderPass.h>
#include <orhi/Semaphore.h>
#include <orhi/ShaderModule.h>
#include <orhi/SwapChain.h>

#include <GLFW/glfw3.h>
#if defined(_WIN32) || defined(_WIN64)
#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__linux__)
#define GLFW_EXPOSE_NATIVE_X11
#endif
#include <GLFW/glfw3native.h>

#include <array>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <vector>

namespace
{
	orhi::data::Window GetWindowDesc(GLFWwindow* window)
	{
#if defined(_WIN32) || defined(_WIN64)
		return orhi::data::WindowsWindow{
			.hwnd = glfwGetWin32Window(window)
		};
#elif defined(__linux__)
		return orhi::data::X11Window{
			.dpy = glfwGetX11Display(),
			.window = glfwGetX11Window(window)
		};
#endif
	}

	orhi::math::Extent2D GetWindowSize(GLFWwindow* window)
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		return { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
	}

	std::vector<std::string> GetGlfwRequiredExtensions()
	{
		uint32_t count = 0;
		const char** extensions = glfwGetRequiredInstanceExtensions(&count);
		return { extensions, extensions + count };
	}

	std::vector<std::byte> ReadShaderFile(const std::filesystem::path& p_fileName)
	{
		std::ifstream file(p_fileName, std::ios::ate | std::ios::binary);
		if (!file.is_open())
		{
			throw std::runtime_error("Failed to open shader file: " + p_fileName.string());
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<std::byte> buffer(fileSize);
		file.seekg(0);
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
		return buffer;
	}

	struct FrameResources
	{
		orhi::CommandBuffer& commandBuffer;
		std::unique_ptr<orhi::Semaphore> imageAvailableSemaphore;
		std::unique_ptr<orhi::Fence> inFlightFence;
	};

	struct SwapImageResources
	{
		orhi::Framebuffer& framebuffer;
		std::unique_ptr<orhi::Semaphore> renderFinishedSemaphore;
	};

	struct PushConstants
	{
		float time;
	};
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "8-push-constants", nullptr, nullptr);

	// Create instance and device
	orhi::Instance instance(orhi::data::InstanceDesc{
		.debug = true,
		.extensions = GetGlfwRequiredExtensions(),
		.window = GetWindowDesc(window)
	});

	const auto& devices = instance.GetSuitableDevices();
	assert(!devices.empty());
	auto& device = instance.CreateDevice(devices.front().id);

	auto optimalSwapChainDesc = device.GetOptimalSwapChainDesc(GetWindowSize(window));

	// Create render pass and pipeline
	orhi::RenderPass renderPass{
		device,
		{
			orhi::data::AttachmentDesc{
				.type = orhi::types::EAttachmentType::COLOR,
				.format = optimalSwapChainDesc.format,
				.finalLayout = orhi::types::ETextureLayout::PRESENT_SRC_KHR,
			}
		}
	};
	orhi::ShaderModule vertexShader{ device, ReadShaderFile("assets/shaders/main.vert.spv") };
	orhi::ShaderModule fragmentShader{ device, ReadShaderFile("assets/shaders/main.frag.spv") };
	
	// Create pipeline layout (empty for this example)
	orhi::PipelineLayout pipelineLayout(
		device,
		{
			.pushConstantRanges = {
				{
					.stageFlags = orhi::types::EShaderStageFlags::VERTEX_BIT,
					.offset = 0,
					.size = sizeof(PushConstants)
				}
			},
		}
	);
	
	orhi::Pipeline pipeline{
		device,
		orhi::data::GraphicsPipelineDesc{
			.stages = {
				{ orhi::types::EShaderStageFlags::VERTEX_BIT, vertexShader },
				{ orhi::types::EShaderStageFlags::FRAGMENT_BIT, fragmentShader },
			},
			.renderPass = renderPass,
			.pipelineLayout = pipelineLayout,
			.colorBlendState = {
				.attachments = std::array<orhi::data::ColorBlendAttachmentStateDesc, 1>()
			},
			.dynamicState = {
				.dynamicStates = std::to_array<orhi::types::EDynamicState>({
					orhi::types::EDynamicState::VIEWPORT,
					orhi::types::EDynamicState::SCISSOR
				})
			}
		}
	};

	// Swap chain and framebuffers
	std::deque<orhi::Framebuffer> framebuffers;
	std::unique_ptr<orhi::SwapChain> swapChain;
	orhi::math::Extent2D windowSize;
	std::vector<SwapImageResources> swapImagesResources;

	auto recreateSwapChain = [&]{
		do
		{
			windowSize = GetWindowSize(window);
			glfwWaitEvents();
		} while (windowSize.width == 0U || windowSize.height == 0U);

		device.WaitIdle();

		framebuffers.clear();
		swapImagesResources.clear();

		swapChain = std::make_unique<orhi::SwapChain>(
			device,
			instance.GetSurfaceHandle(),
			windowSize,
			optimalSwapChainDesc,
			swapChain ? std::make_optional(std::ref(*swapChain)) : std::nullopt
		);

		const uint32_t imageCount = swapChain->GetImageCount();

		swapImagesResources.reserve(imageCount);

		for (uint32_t i = 0; i < imageCount; ++i)
		{
			auto& framebuffer = framebuffers.emplace_back(
				device,
				orhi::data::FramebufferDesc<orhi::BackendTraits>{
					.attachments = { swapChain->GetImageDescriptor(i) },
					.renderPass = renderPass,
					.extent = windowSize
				}
			);

			swapImagesResources.emplace_back(
				framebuffer,
				std::make_unique<orhi::Semaphore>(device)
			);
		}
	};

	recreateSwapChain();

	// Command buffers and synchronization
	constexpr uint8_t k_maxFramesInFlight = 2;
	assert(framebuffers.size() >= k_maxFramesInFlight);

	orhi::CommandPool commandPool{ device };
	auto commandBuffers = commandPool.AllocateCommandBuffers(k_maxFramesInFlight);

	std::vector<FrameResources> framesResources;
	framesResources.reserve(k_maxFramesInFlight);
	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		framesResources.emplace_back(
			commandBuffers[i],
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Fence>(device, true)
		);
	}

	uint32_t imageIndex = 0;
	uint8_t frameIndex = 0;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		auto& frameResources = framesResources[frameIndex];

		frameResources.inFlightFence->Wait();
		imageIndex = swapChain->AcquireNextImage(*frameResources.imageAvailableSemaphore);
		frameResources.inFlightFence->Reset();

		auto& swapImageResources = swapImagesResources[imageIndex];

		auto& commandBuffer = frameResources.commandBuffer;
		commandBuffer.Reset();
		commandBuffer.Begin();
		commandBuffer.BeginRenderPass(
			renderPass,
			swapImageResources.framebuffer,
			windowSize,
			{ orhi::data::ColorClearValue{0.0f, 0.0f, 0.0f, 1.0f} }
		);

		commandBuffer.BindPipeline(orhi::types::EPipelineBindPoint::GRAPHICS, pipeline);

		commandBuffer.SetViewport({
			.x = 0.0f, .y = 0.0f,
			.width = static_cast<float>(windowSize.width),
			.height = static_cast<float>(windowSize.height),
			.minDepth = 0.0f, .maxDepth = 1.0f
		});

		commandBuffer.SetScissor({
			.offset = {0, 0},
			.extent = windowSize
		});

		PushConstants constants{
			.time = static_cast<float>(glfwGetTime())
		};

		commandBuffer.PushConstants(
			pipelineLayout,
			orhi::types::EShaderStageFlags::VERTEX_BIT,
			{ 0, sizeof(PushConstants) },
			&constants
		);

		commandBuffer.Draw(3);
		commandBuffer.EndRenderPass();
		commandBuffer.End();

		device.GetGraphicsAndComputeQueue().Submit(
			{ commandBuffer },
			{ *frameResources.imageAvailableSemaphore },
			{ orhi::types::EPipelineStageFlags::COLOR_ATTACHMENT_OUTPUT_BIT },
			{ *swapImageResources.renderFinishedSemaphore },
			*frameResources.inFlightFence
		);

		try
		{
			device.GetPresentQueue().Present(
				{ *swapImageResources.renderFinishedSemaphore },
				*swapChain,
				imageIndex
			);
		}
		catch (orhi::except::OutOfDateSwapChain)
		{
			recreateSwapChain();
			continue;
		}

		frameIndex = (frameIndex + 1) % k_maxFramesInFlight;
	}

	device.WaitIdle();

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
