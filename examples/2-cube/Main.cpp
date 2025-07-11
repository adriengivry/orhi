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

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

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
#include <orhi/Buffer.h>
#include <orhi/CommandPool.h>
#include <orhi/CommandBuffer.h>
#include <orhi/DescriptorPool.h>
#include <orhi/DescriptorSet.h>
#include <orhi/DescriptorSetLayout.h>
#include <orhi/Queue.h>
#include <orhi/except/OutOfDateSwapChain.h>

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

	struct FrameResources
	{
		orhi::CommandBuffer& commandBuffer;
		orhi::Buffer& ubo;
		orhi::DescriptorSet& descriptorSet;
		std::unique_ptr<orhi::Semaphore> imageAvailableSemaphore;
		std::unique_ptr<orhi::Fence> inFlightFence;
	};

	struct SwapImageResources
	{
		orhi::Framebuffer& framebuffer;
		std::unique_ptr<orhi::Semaphore> renderFinishedSemaphore;
	};

	struct Vertex
	{
		glm::vec3 pos;
		glm::vec3 normal;
	};

	template<class T>
	struct VertexInputDescription
	{
		static auto GetBindingDescription();
		static auto GetAttributeDescriptions();
	};

	template<>
	struct VertexInputDescription<Vertex>
	{
		static auto GetBindingDescription()
		{
			return std::to_array<orhi::data::VertexBindingDesc>({
				{
					.binding = 0,
					.stride = sizeof(Vertex),
				}
			});
		}

		static auto GetAttributeDescriptions()
		{
			return std::to_array<orhi::data::VertexAttributeDesc>({
				{
					.binding = 0,
					.location = 0,
					.offset = offsetof(Vertex, pos),
					.format = orhi::types::EFormat::R32G32B32_SFLOAT
				},
				{
					.binding = 0,
					.location = 1,
					.offset = offsetof(Vertex, normal),
					.format = orhi::types::EFormat::R32G32B32_SFLOAT
				}
			});
		}
	};

	constexpr auto k_vertices = std::to_array<Vertex>({
		// Front face (normal: 0, 0, 1)
		{{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // 0
		{{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // 1
		{{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // 2
		{{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}}, // 3
		// Right face (normal: 1, 0, 0)
		{{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // 4
		{{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // 5
		{{ 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}}, // 6
		{{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}}, // 7
		// Back face (normal: 0, 0, -1)
		{{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}}, // 8
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}}, // 9
		{{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}}, // 10
		{{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}}, // 11
		// Left face (normal: -1, 0, 0)
		{{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}}, // 12
		{{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}}, // 13
		{{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}}, // 14
		{{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}}, // 15
		// Top face (normal: 0, 1, 0)
		{{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, // 16
		{{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}}, // 17
		{{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}, // 18
		{{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}}, // 19
		// Bottom face (normal: 0, -1, 0)
		{{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}}, // 20
		{{ 0.5f, -0.5f, -0.5f}, {0.0f, -1.0f, 0.0f}}, // 21
		{{ 0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}}, // 22
		{{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f, 0.0f}}, // 23
	});

	constexpr auto k_indices = std::to_array<uint32_t>({
		// Front face
		0, 1, 2,  2, 3, 0,
		// Right face
		4, 5, 6,  6, 7, 4,
		// Back face
		8, 9, 10,  10, 11, 8,
		// Left face
		12, 13, 14,  14, 15, 12,
		// Top face
		16, 17, 18,  18, 19, 16,
		// Bottom face
		20, 21, 22,  22, 23, 20,
	});

	struct UniformBufferObject
	{
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "2-cube", nullptr, nullptr);

	// Create backend and device
	orhi::Backend backend(orhi::data::BackendDesc{
		.debug = true,
		.extensions = GetGlfwRequiredExtensions(),
		.win32_windowHandle = glfwGetWin32Window(window),
		.win32_instanceHandle = GetModuleHandle(nullptr)
	});

	const auto& devices = backend.GetSuitableDevices();
	assert(!devices.empty());
	auto& device = backend.CreateDevice(devices.front().id);

	auto optimalSwapChainDesc = device.GetOptimalSwapChainDesc(GetWindowSize(window));

	// Create a CPU-side buffer to hold vertices
	auto hostVertexBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = sizeof(k_vertices),
			.usage = orhi::types::EBufferUsageFlags::TRANSFER_SRC_BIT
		}
	);
	hostVertexBuffer->Allocate(
		orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT |
		orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT
	);
	hostVertexBuffer->Upload(k_vertices.data());

	// Create a CPU-side buffer to hold indices
	std::unique_ptr<orhi::Buffer> hostIndexBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = sizeof(k_indices),
			.usage = orhi::types::EBufferUsageFlags::TRANSFER_SRC_BIT
		}
	);
	hostIndexBuffer->Allocate(
		orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT |
		orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT
	);
	hostIndexBuffer->Upload(k_indices.data());

	// Create a GPU-side buffer to hold vertices
	std::unique_ptr<orhi::Buffer> deviceVertexBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = sizeof(k_vertices),
			.usage = orhi::types::EBufferUsageFlags::TRANSFER_DST_BIT | orhi::types::EBufferUsageFlags::VERTEX_BUFFER_BIT
		}
	);
	deviceVertexBuffer->Allocate(orhi::types::EMemoryPropertyFlags::DEVICE_LOCAL_BIT);

	// Create a GPU-side buffer to hold indices
	auto deviceIndexBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = sizeof(k_indices),
			.usage = orhi::types::EBufferUsageFlags::TRANSFER_DST_BIT | orhi::types::EBufferUsageFlags::INDEX_BUFFER_BIT
		}
	);
	deviceIndexBuffer->Allocate(orhi::types::EMemoryPropertyFlags::DEVICE_LOCAL_BIT);

	// Create a descriptor layout for the uniform buffer
	auto descriptorSetLayout = std::make_unique<orhi::DescriptorSetLayout>(
		device,
		std::initializer_list<orhi::data::DescriptorBinding>{
			{
				.binding = 0,
				.type = orhi::types::EDescriptorType::UNIFORM_BUFFER,
				.stageFlags = orhi::types::EShaderStageFlags::VERTEX_BIT,
			}
		}
	);

	// Create render pass and pipeline
	orhi::RenderPass renderPass{ device, optimalSwapChainDesc.format };
	orhi::ShaderModule vertexShader{ device, ReadShaderFile("assets/shaders/main.vert.spv") };
	orhi::ShaderModule fragmentShader{ device, ReadShaderFile("assets/shaders/main.frag.spv") };

	orhi::GraphicsPipeline pipeline{
		device,
		{
			.stages = {
				{ orhi::types::EShaderStageFlags::VERTEX_BIT, vertexShader },
				{ orhi::types::EShaderStageFlags::FRAGMENT_BIT, fragmentShader },
			},
			.renderPass = renderPass,
			.descriptorSetLayouts = std::to_array({std::ref(*descriptorSetLayout)}),
			.vertexInputState{
				.vertexBindings = VertexInputDescription<Vertex>::GetBindingDescription(),
				.vertexAttributes = VertexInputDescription<Vertex>::GetAttributeDescriptions()
			},
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
	std::vector<orhi::Framebuffer> framebuffers;
	std::unique_ptr<orhi::SwapChain> swapChain;
	std::pair<uint32_t, uint32_t> windowSize;
	std::vector<SwapImageResources> swapImagesResources;

	auto recreateSwapChain = [&] {
		do
		{
			windowSize = GetWindowSize(window);
			glfwWaitEvents();
		} while (windowSize.first == 0U || windowSize.second == 0U);

		device.WaitIdle();
		framebuffers.clear();
		swapImagesResources.clear();

		swapChain = std::make_unique<orhi::SwapChain>(
			device,
			backend.GetSurfaceHandle(),
			windowSize,
			optimalSwapChainDesc,
			swapChain ? std::make_optional(std::ref(*swapChain)) : std::nullopt
		);

		framebuffers = swapChain->CreateFramebuffers(renderPass);

		swapImagesResources.reserve(framebuffers.size());
		for (uint32_t i = 0; i < framebuffers.size(); ++i)
		{
			swapImagesResources.emplace_back(
				framebuffers[i],
				std::make_unique<orhi::Semaphore>(device)
			);
		}
	};

	recreateSwapChain();

	// Command buffers and synchronization
	constexpr uint8_t k_maxFramesInFlight = 2;
	assert(framebuffers.size() >= k_maxFramesInFlight);

	// Create UBOs (one for each frame)
	std::vector<orhi::Buffer> ubos;
	ubos.reserve(k_maxFramesInFlight);
	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		auto& ubo = ubos.emplace_back(
			device,
			orhi::data::BufferDesc{
				.size = sizeof(UniformBufferObject),
				.usage = orhi::types::EBufferUsageFlags::UNIFORM_BUFFER_BIT
			}
		);

		ubo.Allocate(orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT | orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT);
	}

	// Create a descriptor pool to allocate descriptor sets
	auto descriptorPool = std::make_unique<orhi::DescriptorPool>(
		device,
		orhi::data::DescriptorPoolDesc{
			.flags = orhi::types::EDescriptorPoolCreateFlags::NONE,
			.maxSets = k_maxFramesInFlight,
			.poolSizes = {
				{ orhi::types::EDescriptorType::UNIFORM_BUFFER, k_maxFramesInFlight }
			}
		}
	);

	// Create a descriptor set for each frame
	auto descriptorSets = descriptorPool->AllocateDescriptorSets(
		*descriptorSetLayout,
		k_maxFramesInFlight
	);

	// Update each descriptor set (attach each uniform buffer to each descriptor set)
	for (size_t i = 0; i < k_maxFramesInFlight; i++)
	{
		descriptorSets[i].get().Write(
			{
				{
					0,
					orhi::data::BufferDescriptorWriteInfo{
						.bufferDescriptor = ubos[i],
						.descriptorType = orhi::types::EDescriptorType::UNIFORM_BUFFER
					}
				}
			}
		);
	}

	orhi::CommandPool commandPool{ device };
	auto commandBuffers = commandPool.AllocateCommandBuffers(k_maxFramesInFlight);
	auto& transferCommandBuffer = commandPool.AllocateCommandBuffers(1).front().get();

	// Upload CPU (host) buffers to the GPU (device)
	transferCommandBuffer.Begin(orhi::types::ECommandBufferUsageFlags::ONE_TIME_SUBMIT_BIT);
	transferCommandBuffer.CopyBuffer(*hostVertexBuffer, *deviceVertexBuffer);
	transferCommandBuffer.CopyBuffer(*hostIndexBuffer, *deviceIndexBuffer);
	transferCommandBuffer.End();
	device.GetGraphicsQueue().As<orhi::Queue*>()->Submit({ transferCommandBuffer });
	device.WaitIdle();

	// At this point we don't need the client copy of these buffers anymore
	hostVertexBuffer->Deallocate();
	hostIndexBuffer->Deallocate();

	std::vector<FrameResources> framesResources;
	framesResources.reserve(k_maxFramesInFlight);
	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		framesResources.emplace_back(
			commandBuffers[i],
			ubos[i],
			descriptorSets[i],
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
		commandBuffer.BeginRenderPass(renderPass, swapImageResources.framebuffer, windowSize);
		commandBuffer.BindPipeline(orhi::types::EPipelineBindPoint::GRAPHICS, pipeline.GetNativeHandle());

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

		const float time = static_cast<float>(glfwGetTime());

		// Update UBO data each frame
		UniformBufferObject uboData{
			.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
			.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
			.proj = glm::perspective(glm::radians(45.0f), windowSize.first / (float)windowSize.second, 0.1f, 10.0f)
		};

		uboData.proj[1][1] *= -1;

		frameResources.ubo.Upload(&uboData);

		commandBuffer.BindVertexBuffers(
			std::to_array({ std::ref(*deviceVertexBuffer) }),
			std::to_array<uint64_t>({ 0 })
		);

		commandBuffer.BindIndexBuffer(
			*deviceIndexBuffer
		);

		commandBuffer.BindDescriptorSets(
			std::to_array({ std::ref(frameResources.descriptorSet) }),
			pipeline.GetLayoutHandle()
		);

		commandBuffer.DrawIndexed(static_cast<uint32_t>(k_indices.size()));

		commandBuffer.EndRenderPass();
		commandBuffer.End();

		device.GetGraphicsQueue().As<orhi::Queue*>()->Submit(
			{ commandBuffer },
			{ *frameResources.imageAvailableSemaphore },
			{ *swapImageResources.renderFinishedSemaphore },
			*frameResources.inFlightFence
		);

		try
		{
			device.GetPresentQueue().As<orhi::Queue*>()->Present(
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
