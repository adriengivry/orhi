/**
* @project: vulkan-sandbox
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
#include <array>
#include <iostream>
#include <vector>
#include <span>
#include <ranges>
#include <filesystem>
#include <fstream>

#include <orhi/Backend.h>
#include <orhi/RenderPass.h>
#include <orhi/ShaderModule.h>
#include <orhi/Buffer.h>
#include <orhi/DescriptorSetLayout.h>
#include <orhi/GraphicsPipeline.h>
#include <orhi/Framebuffer.h>
#include <orhi/Semaphore.h>
#include <orhi/Fence.h>
#include <orhi/SwapChain.h>

namespace
{
	std::pair<uint32_t, uint32_t> GetWindowSize(GLFWwindow* p_window)
	{
		int width, height;
		glfwGetFramebufferSize(p_window, &width, &height);
		return {
			static_cast<uint32_t>(width),
			static_cast<uint32_t>(height)
		};
	}

	std::vector<std::string> GetGlfwRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<std::string> requiredExtensions;
		requiredExtensions.reserve(glfwExtensionCount);
		for (uint32_t i = 0; i < glfwExtensionCount; ++i)
		{
			requiredExtensions.push_back(glfwExtensions[i]);
		}

		return requiredExtensions;
	}

	std::vector<std::byte> ReadShaderFile(const std::filesystem::path p_fileName)
	{
		assert(std::filesystem::exists(p_fileName));

		std::ifstream file(p_fileName, std::ios::ate | std::ios::binary);

		if (!file.is_open())
		{
			throw std::runtime_error("failed to open shader file: " + p_fileName.string());
		}

		size_t fileSize = static_cast<size_t>(file.tellg());
		std::vector<std::byte> buffer(fileSize);
		file.seekg(0);
		file.read(reinterpret_cast<char*>(buffer.data()), fileSize);
		file.close();
		return buffer;
	}

	struct Vertex
	{
		glm::vec2 pos;
		glm::vec3 color;
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
					.format = orhi::types::EFormat::R32G32_SFLOAT
				},
				{
					.binding = 0,
					.location = 1,
					.offset = offsetof(Vertex, color),
					.format = orhi::types::EFormat::R32G32B32_SFLOAT
				}
			});
		}
	};

	constexpr auto k_vertices = std::to_array<Vertex>({
		{{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
		{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
		{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
	});

	constexpr auto k_indices = std::to_array<uint32_t>({
		0, 1, 2,
		2, 3, 0
	});

	struct FrameData
	{
		// orhi::CommandBuffer& commandBuffer;
		// orhi::Buffer& ubo;
		// orhi::DescriptorSet& descriptorSet;
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
	GLFWwindow* window = glfwCreateWindow(800, 600, "0-vulkan", nullptr, nullptr);

	// Create backend
	auto backend = std::make_unique<orhi::Backend>(
		orhi::data::BackendDesc{
			.debug = true,
			.extensions = GetGlfwRequiredExtensions(),
			.win32_windowHandle = glfwGetWin32Window(window),
			.win32_instanceHandle = GetModuleHandle(nullptr)
		}
	);

	// Make sure there is at least one suitable device
	const auto& devices = backend->GetSuitableDevices();

	assert(!devices.empty());

	// Select the first suitable device
	auto& device = backend->CreateDevice(devices.front().id);

	auto optimalSwapChainDesc = device.GetOptimalSwapChainDesc(
		GetWindowSize(window)
	);

	auto renderPass = std::make_unique<orhi::RenderPass>(
		device,
		optimalSwapChainDesc.format
	);

	auto vertexShaderModule = std::make_unique<orhi::ShaderModule>(
		device,
		ReadShaderFile("assets/shaders/main.vert.spv")
	);

	auto fragmentShaderModule = std::make_unique<orhi::ShaderModule>(
		device,
		ReadShaderFile("assets/shaders/main.frag.spv")
	);

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

	auto graphicsPipeline = std::make_unique<orhi::GraphicsPipeline>(
		device,
		orhi::GraphicsPipeline::Desc{
			.stages = {
				{orhi::types::EShaderStageFlags::VERTEX_BIT, std::ref(*vertexShaderModule)},
				{orhi::types::EShaderStageFlags::FRAGMENT_BIT, std::ref(*fragmentShaderModule)},
			},
			.renderPass = *renderPass,
			.vertexAttributes = VertexInputDescription<Vertex>::GetAttributeDescriptions(),
			.vertexBindings = VertexInputDescription<Vertex>::GetBindingDescription(),
			.descriptorSetLayouts = std::to_array({std::ref(*descriptorSetLayout)})
		}
	);

	constexpr uint8_t k_maxFramesInFlight = 2;

	std::vector<FrameData> frameDataArray;
	frameDataArray.reserve(k_maxFramesInFlight);
	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		frameDataArray.emplace_back(
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Semaphore>(device),
			std::make_unique<orhi::Fence>(device, true)
		);
	}

	std::vector<orhi::Framebuffer> framebuffers;
	std::unique_ptr<orhi::SwapChain> swapChain;

	auto recreateSwapChain = [&] {
		std::pair<uint32_t, uint32_t> windowSize = { 0, 0 };

		for (windowSize = GetWindowSize(window); windowSize.first == 0 || windowSize.second == 0;)
		{
			glfwWaitEvents();
		}

		device.WaitIdle();
		framebuffers.clear();
		swapChain.reset();

		swapChain = std::make_unique<orhi::SwapChain>(
			device,
			backend->GetSurfaceHandle(),
			windowSize,
			optimalSwapChainDesc
		);

		framebuffers = swapChain->CreateFramebuffers(*renderPass);
	};

	recreateSwapChain();

	uint32_t swapImageIndex = 0;
	uint8_t currentFrameIndex = 0;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		FrameData& frameData = frameDataArray[currentFrameIndex];

		// device.WaitForFences({ *frameData.inFlightFence });

		swapImageIndex = swapChain->AcquireNextImage(
			*frameData.imageAvailableSemaphore
		);

		// device.ResetFences({ *frameData.inFlightFence });

		currentFrameIndex = (currentFrameIndex + 1) % k_maxFramesInFlight;
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return EXIT_SUCCESS;
}
