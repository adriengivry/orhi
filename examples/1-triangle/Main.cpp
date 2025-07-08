/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <GLFW/glfw3.h>

#if defined(_WIN32) || defined(_WIN64)
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif

#include <cassert>
#include <vector>
#include <filesystem>
#include <fstream>
#include <array>

#include <orhi/Backend.h>
#include <orhi/RenderPass.h>
#include <orhi/ShaderModule.h>
#include <orhi/GraphicsPipeline.h>
#include <orhi/Framebuffer.h>
#include <orhi/Semaphore.h>
#include <orhi/Fence.h>
#include <orhi/SwapChain.h>
#include <orhi/CommandPool.h>
#include <orhi/CommandBuffer.h>
#include <orhi/Queue.h>
#include <orhi/except/OutOfDateSwapChain.h>
#include <orhi/types/EPrimitiveTopology.h>
#include <orhi/types/EPolygonMode.h>
#include <orhi/types/ECullModeFlags.h>
#include <orhi/types/EFrontFace.h>
#include <orhi/types/ESampleCountFlags.h>
#include <orhi/types/ECompareOp.h>
#include <orhi/types/ELogicOp.h>
#include <orhi/types/EBlendFactor.h>
#include <orhi/types/EBlendOp.h>
#include <orhi/types/EColorComponentFlags.h>
#include <orhi/types/EDynamicState.h>

namespace
{
	std::pair<uint32_t, uint32_t> GetWindowSize(GLFWwindow* window)
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

	struct FrameData
	{
		orhi::CommandBuffer& commandBuffer;
		std::unique_ptr<orhi::Semaphore> imageAvailableSemaphore;
		std::unique_ptr<orhi::Semaphore> renderFinishedSemaphore;
		std::unique_ptr<orhi::Fence> inFlightFence;
	};
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", nullptr, nullptr);

	// Create backend and device
	auto backend = std::make_unique<orhi::Backend>(orhi::data::BackendDesc{
		.debug = true,
		.extensions = GetGlfwRequiredExtensions(),
		.win32_windowHandle = glfwGetWin32Window(window),
		.win32_instanceHandle = GetModuleHandle(nullptr)
	});

	const auto& devices = backend->GetSuitableDevices();
	assert(!devices.empty());
	auto& device = backend->CreateDevice(devices.front().id);

	auto optimalSwapChainDesc = device.GetOptimalSwapChainDesc(GetWindowSize(window));

	// Create render pass and pipeline
	auto renderPass = std::make_unique<orhi::RenderPass>(device, optimalSwapChainDesc.format);
	auto vertexShader = std::make_unique<orhi::ShaderModule>(device, ReadShaderFile("assets/shaders/main.vert.spv"));
	auto fragmentShader = std::make_unique<orhi::ShaderModule>(device, ReadShaderFile("assets/shaders/main.frag.spv"));
	
	auto pipeline = std::make_unique<orhi::GraphicsPipeline>(device, orhi::GraphicsPipeline::Desc{
		.stages = {
			{orhi::types::EShaderStageFlags::VERTEX_BIT, std::ref(*vertexShader)},
			{orhi::types::EShaderStageFlags::FRAGMENT_BIT, std::ref(*fragmentShader)},
		},
		.renderPass = *renderPass,
		.colorBlendState = {
			.attachments = std::array<orhi::data::ColorBlendAttachmentStateDesc, 1>()
		},
		.dynamicState = {
			.dynamicStates = std::to_array<orhi::types::EDynamicState>({
				orhi::types::EDynamicState::VIEWPORT,
				orhi::types::EDynamicState::SCISSOR
			})
		}
	});

	// Swap chain and framebuffers
	std::vector<orhi::Framebuffer> framebuffers;
	std::unique_ptr<orhi::SwapChain> swapChain;
	std::pair<uint32_t, uint32_t> windowSize;

	auto recreateSwapChain = [&]() {
		while ((windowSize = GetWindowSize(window)).first == 0 || windowSize.second == 0)
		{
			glfwWaitEvents();
		}

		device.WaitIdle();
		framebuffers.clear();
		swapChain = std::make_unique<orhi::SwapChain>(device, backend->GetSurfaceHandle(), windowSize, optimalSwapChainDesc);
		framebuffers = swapChain->CreateFramebuffers(*renderPass);
	};

	recreateSwapChain();

	// Command buffers and synchronization
	constexpr uint8_t maxFramesInFlight = 2;
	assert(framebuffers.size() >= maxFramesInFlight);

	auto commandPool = std::make_unique<orhi::CommandPool>(device);
	auto commandBuffers = commandPool->AllocateCommandBuffers(maxFramesInFlight);

	std::vector<FrameData> frames;
	frames.reserve(maxFramesInFlight);
	for (uint8_t i = 0; i < maxFramesInFlight; ++i)
	{
		frames.emplace_back(
			commandBuffers[i],
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Fence>(device, true)
		);
	}

	uint32_t imageIndex = 0;
	uint8_t frameIndex = 0;

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		auto& frame = frames[frameIndex];
		frame.inFlightFence->Wait();
		
		imageIndex = swapChain->AcquireNextImage(*frame.imageAvailableSemaphore);
		frame.inFlightFence->Reset();

		auto& commandBuffer = frame.commandBuffer;
		commandBuffer.Reset();
		commandBuffer.Begin();
		commandBuffer.BeginRenderPass(*renderPass, framebuffers[imageIndex], windowSize);
		commandBuffer.BindPipeline(orhi::types::EPipelineBindPoint::GRAPHICS, pipeline->GetNativeHandle());

		commandBuffer.SetViewport({
			.x = 0.0f, .y = 0.0f,
			.width = static_cast<float>(windowSize.first),
			.height = static_cast<float>(windowSize.second),
			.minDepth = 0.0f, .maxDepth = 1.0f
		});

		commandBuffer.SetScissor({
			.offset = {0, 0},
			.extent = windowSize
		});

		commandBuffer.Draw(3);
		commandBuffer.EndRenderPass();
		commandBuffer.End();

		device.GetGraphicsQueue().As<orhi::Queue*>()->Submit(
			{ commandBuffer },
			{ *frame.imageAvailableSemaphore },
			{ *frame.renderFinishedSemaphore },
			*frame.inFlightFence
		);

		try
		{
			device.GetPresentQueue().As<orhi::Queue*>()->Present(
				{ *frame.renderFinishedSemaphore },
				*swapChain,
				imageIndex
			);
		}
		catch (orhi::except::OutOfDateSwapChain)
		{
			recreateSwapChain();
			continue;
		}

		frameIndex = (frameIndex + 1) % maxFramesInFlight;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
