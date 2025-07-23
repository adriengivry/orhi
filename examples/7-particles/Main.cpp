/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/BackendTraits.h>
#include <orhi/Buffer.h>
#include <orhi/Descriptor.h>
#include <orhi/DescriptorPool.h>
#include <orhi/DescriptorSet.h>
#include <orhi/DescriptorSetLayout.h>
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

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <array>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <random>
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
		orhi::CommandBuffer& graphicsCommandBuffer;
		orhi::CommandBuffer& computeCommandBuffer;
		orhi::DescriptorSet& descriptorSet;
		std::unique_ptr<orhi::Buffer> parametersBuffer;
		std::unique_ptr<orhi::Buffer> particlesBuffer;
		std::unique_ptr<orhi::Semaphore> imageAvailableSemaphore;
		std::unique_ptr<orhi::Fence> inFlightFence;
		std::unique_ptr<orhi::Semaphore> computeFinishedSemaphore;
		std::unique_ptr<orhi::Fence> computeInFlightFence;
	};

	struct SwapImageResources
	{
		orhi::Framebuffer& framebuffer;
		std::unique_ptr<orhi::Semaphore> renderFinishedSemaphore;
	};

	struct Particle
	{
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec4 color;
	};

	template<class T>
	struct VertexInputDescription
	{
		static auto GetBindingDescription();
		static auto GetAttributeDescriptions();
	};

	template<>
	struct VertexInputDescription<Particle>
	{
		static auto GetBindingDescription()
		{
			return std::to_array<orhi::data::VertexBindingDesc>({
				{
					.binding = 0,
					.stride = sizeof(Particle),
				}
			});
		}

		static auto GetAttributeDescriptions()
		{
			return std::to_array<orhi::data::VertexAttributeDesc>({
				{
					.binding = 0,
					.location = 0,
					.offset = offsetof(Particle, position),
					.format = orhi::types::EFormat::R32G32_SFLOAT
				},
				{
					.binding = 0,
					.location = 1,
					.offset = offsetof(Particle, color),
					.format = orhi::types::EFormat::R32G32B32_SFLOAT
				}
			});
		}
	};
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "7-particles", nullptr, nullptr);

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

	orhi::PipelineLayout graphicsPipelineLayout(device);
	
	orhi::Pipeline graphicsPipeline{
		device,
		orhi::data::GraphicsPipelineDesc<orhi::BackendTraits>{
			.stages = {
				{ orhi::types::EShaderStageFlags::VERTEX_BIT, vertexShader },
				{ orhi::types::EShaderStageFlags::FRAGMENT_BIT, fragmentShader },
			},
			.renderPass = renderPass,
			.pipelineLayout = graphicsPipelineLayout,
			.vertexInputState = {
				.vertexBindings = VertexInputDescription<Particle>::GetBindingDescription(),
				.vertexAttributes = VertexInputDescription<Particle>::GetAttributeDescriptions()
			},
			.inputAssemblyState = {
				.topology = orhi::types::EPrimitiveTopology::POINT_LIST,
				.primitiveRestartEnable = false
			},
			.rasterizationState = {
				.polygonMode = orhi::types::EPolygonMode::FILL,
				.cullMode = orhi::types::ECullModeFlags::BACK_BIT,
			},
			.colorBlendState = {
				.attachments = std::to_array({
					orhi::data::ColorBlendAttachmentStateDesc{
						.blendEnable = true
					}
				}),
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
	auto graphicsCommandBuffers = commandPool.AllocateCommandBuffers(k_maxFramesInFlight);
	auto computeCommandBuffers = commandPool.AllocateCommandBuffers(k_maxFramesInFlight);
	auto& transferCommandBuffer = commandPool.AllocateCommandBuffers(1).front().get();

	orhi::DescriptorSetLayout descriptorSetLayout{
		device,
		{
			orhi::data::DescriptorBinding{
				.binding = 0,
				.type = orhi::types::EDescriptorType::UNIFORM_BUFFER,
				.stageFlags = orhi::types::EShaderStageFlags::COMPUTE_BIT
			},
			orhi::data::DescriptorBinding{
				.binding = 1,
				.type = orhi::types::EDescriptorType::STORAGE_BUFFER,
				.stageFlags = orhi::types::EShaderStageFlags::COMPUTE_BIT
			},
			orhi::data::DescriptorBinding{
				.binding = 2,
				.type = orhi::types::EDescriptorType::STORAGE_BUFFER,
				.stageFlags = orhi::types::EShaderStageFlags::COMPUTE_BIT
			}
		},
	};

	// Create pipeline layout for compute pipeline
	orhi::PipelineLayout computePipelineLayout{
		device,
		orhi::data::PipelineLayoutDesc<orhi::BackendTraits>{
			.descriptorSetLayouts = std::to_array({ std::ref(descriptorSetLayout) })
		}
	};

	orhi::ShaderModule computeShader{ device, ReadShaderFile("assets/shaders/main.comp.spv") };

	orhi::Pipeline computePipeline{
		device,
		orhi::data::ComputePipelineDesc<orhi::BackendTraits>{
			.shader = computeShader,
			.pipelineLayout = computePipelineLayout
		}
	};

	constexpr uint32_t k_particleCount = 1024;

	orhi::Buffer hostParticleBuffer(
		device,
		orhi::data::BufferDesc{
			.size = k_particleCount * sizeof(Particle), // Example size for particle data
			.usage = orhi::types::EBufferUsageFlags::TRANSFER_SRC_BIT
		}
	);
	hostParticleBuffer.Allocate(
		orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT |
		orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT
	);

	// Initialize particles
	std::default_random_engine rndEngine((unsigned)time(nullptr));
	std::uniform_real_distribution<float> rndDist(0.0f, 1.0f);

	// Initial particle positions on a circle
	std::vector<Particle> particles(k_particleCount);
	for (auto& particle : particles)
	{
		float r = 0.25f * sqrt(rndDist(rndEngine));
		float theta = rndDist(rndEngine) * 2.0f * 3.14159265358979323846f;
		float x = r * cos(theta);
		float y = r * sin(theta);
		particle.position = glm::vec2(x, y);
		particle.velocity = glm::normalize(glm::vec2(x, y));
		particle.color = glm::vec4(rndDist(rndEngine), rndDist(rndEngine), rndDist(rndEngine), 1.0f);
	}

	hostParticleBuffer.Upload(particles.data());

	orhi::DescriptorPool descriptorPool{
		device,
		orhi::data::DescriptorPoolDesc{
			.maxSets = k_maxFramesInFlight * 3,
			.poolSizes = {
				{ orhi::types::EDescriptorType::UNIFORM_BUFFER, k_maxFramesInFlight },
				{ orhi::types::EDescriptorType::STORAGE_BUFFER, k_maxFramesInFlight },
				{ orhi::types::EDescriptorType::STORAGE_BUFFER, k_maxFramesInFlight },
			}
		}
	};

	auto descriptorSets = descriptorPool.AllocateDescriptorSets(
		descriptorSetLayout,
		k_maxFramesInFlight
	);

	std::vector<FrameResources> framesResources;
	framesResources.reserve(k_maxFramesInFlight);
	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		auto& frameResource = framesResources.emplace_back(
			graphicsCommandBuffers[i],
			computeCommandBuffers[i],
			descriptorSets[i],
			std::make_unique<orhi::Buffer>(
				device,
				orhi::data::BufferDesc{
					.size = sizeof(float),
					.usage =
						orhi::types::EBufferUsageFlags::UNIFORM_BUFFER_BIT |
						orhi::types::EBufferUsageFlags::TRANSFER_DST_BIT
				}
			),
			std::make_unique<orhi::Buffer>(
				device,
				orhi::data::BufferDesc{
					.size = k_particleCount * sizeof(Particle), // Example size for particle data
					.usage =
						orhi::types::EBufferUsageFlags::STORAGE_BUFFER_BIT |
						orhi::types::EBufferUsageFlags::VERTEX_BUFFER_BIT |
						orhi::types::EBufferUsageFlags::TRANSFER_DST_BIT
				}
			),
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Fence>(device, true),
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Fence>(device, true)
		);

		frameResource.parametersBuffer->Allocate(
			orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT
		);

		frameResource.particlesBuffer->Allocate(
			orhi::types::EMemoryPropertyFlags::DEVICE_LOCAL_BIT
		);
	}

	transferCommandBuffer.Begin(orhi::types::ECommandBufferUsageFlags::ONE_TIME_SUBMIT_BIT);

	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		auto& currentFrameResources = framesResources[i];
		auto& previousFrameResources = framesResources[(i + k_maxFramesInFlight - 1) % k_maxFramesInFlight];

		currentFrameResources.descriptorSet.Write({
			{
				0,
				orhi::data::BufferDescriptorWriteInfo{
					.bufferDescriptor = *currentFrameResources.parametersBuffer,
					.descriptorType = orhi::types::EDescriptorType::UNIFORM_BUFFER
				}
			},
			{
				1,
				orhi::data::BufferDescriptorWriteInfo{
					.bufferDescriptor = *previousFrameResources.particlesBuffer,
					.descriptorType = orhi::types::EDescriptorType::STORAGE_BUFFER
				}
			},
			{
				2,
				orhi::data::BufferDescriptorWriteInfo{
					.bufferDescriptor = *currentFrameResources.particlesBuffer,
					.descriptorType = orhi::types::EDescriptorType::STORAGE_BUFFER
				}
			}
		});

		transferCommandBuffer.CopyBuffer(hostParticleBuffer, *currentFrameResources.particlesBuffer);
	}

	transferCommandBuffer.End();
	device.GetGraphicsAndComputeQueue().Submit(
		{ transferCommandBuffer }
	);
	device.WaitIdle();

	uint32_t imageIndex = 0;
	uint8_t frameIndex = 0;

	float previousTime = static_cast<float>(glfwGetTime());

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		auto& frameResources = framesResources[frameIndex];

		frameResources.computeInFlightFence->Wait();
		float currentTime = static_cast<float>(glfwGetTime());
		float deltaTime = currentTime - previousTime;
		frameResources.parametersBuffer->Upload(
			&deltaTime
		);
		previousTime = currentTime;
		frameResources.computeInFlightFence->Reset();

		auto& computeCommandBuffer = frameResources.computeCommandBuffer;
		computeCommandBuffer.Reset();
		computeCommandBuffer.Begin();
		computeCommandBuffer.BindPipeline(orhi::types::EPipelineBindPoint::COMPUTE, computePipeline);
		computeCommandBuffer.BindDescriptorSets(
			std::to_array({ std::ref(frameResources.descriptorSet) }),
			computePipelineLayout,
			orhi::types::EPipelineBindPoint::COMPUTE
		);
		computeCommandBuffer.Dispatch(
			(k_particleCount + 255) / 256,
			1,
			1
		);
		computeCommandBuffer.End();
		device.GetGraphicsAndComputeQueue().Submit(
			{ computeCommandBuffer },
			{ },
			{ },
			{ *frameResources.computeFinishedSemaphore },
			*frameResources.computeInFlightFence
		);

		frameResources.inFlightFence->Wait();
		imageIndex = swapChain->AcquireNextImage(*frameResources.imageAvailableSemaphore);
		frameResources.inFlightFence->Reset();

		auto& swapImageResources = swapImagesResources[imageIndex];

		auto& graphicsCommandBuffer = frameResources.graphicsCommandBuffer;
		graphicsCommandBuffer.Reset();
		graphicsCommandBuffer.Begin();
		graphicsCommandBuffer.BeginRenderPass(
			renderPass,
			swapImageResources.framebuffer,
			windowSize,
			{ orhi::data::ColorClearValue{0.0f, 0.0f, 0.0f, 1.0f} }
		);

		graphicsCommandBuffer.BindPipeline(orhi::types::EPipelineBindPoint::GRAPHICS, graphicsPipeline);

		graphicsCommandBuffer.SetViewport({
			.x = 0.0f, .y = 0.0f,
			.width = static_cast<float>(windowSize.width),
			.height = static_cast<float>(windowSize.height),
			.minDepth = 0.0f, .maxDepth = 1.0f
		});

		graphicsCommandBuffer.SetScissor({
			.offset = {0, 0},
			.extent = windowSize
		});

		graphicsCommandBuffer.BindVertexBuffers(
			std::to_array({ std::ref(*frameResources.particlesBuffer) }),
			std::to_array<uint64_t>({ 0 })
		);

		graphicsCommandBuffer.Draw(k_particleCount);
		graphicsCommandBuffer.EndRenderPass();
		graphicsCommandBuffer.End();

		device.GetGraphicsAndComputeQueue().Submit(
			{ graphicsCommandBuffer },
			{	
				*frameResources.computeFinishedSemaphore,
				*frameResources.imageAvailableSemaphore
			},
			{
				orhi::types::EPipelineStageFlags::VERTEX_INPUT_BIT,
				orhi::types::EPipelineStageFlags::COLOR_ATTACHMENT_OUTPUT_BIT
			},
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
