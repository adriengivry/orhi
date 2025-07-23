/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/BackendTraits.h>
#include <orhi/Buffer.h>
#include <orhi/CommandBuffer.h>
#include <orhi/CommandPool.h>
#include <orhi/Descriptor.h>
#include <orhi/DescriptorPool.h>
#include <orhi/DescriptorSet.h>
#include <orhi/DescriptorSetLayout.h>
#include <orhi/Device.h>
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
#include <orhi/Texture.h>

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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

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
		glm::vec2 pos;
		glm::vec2 uv;
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
					.offset = offsetof(Vertex, uv),
					.format = orhi::types::EFormat::R32G32_SFLOAT
				}
			});
		}
	};

	constexpr auto k_vertices = std::to_array<Vertex>({
		{{-0.5f, -0.5f}, {0.0f, 0.0f}},
		{{ 0.5f, -0.5f}, {1.0f, 0.0f}},
		{{ 0.5f,  0.5f}, {1.0f, 1.0f}},
		{{-0.5f,  0.5f}, {0.0f, 1.0f}},
	});

	constexpr auto k_indices = std::to_array<uint32_t>({
		2, 1, 0,
		0, 3, 2,
	});
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "5-mipmaps", nullptr, nullptr);

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

	auto vertexBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = sizeof(k_vertices),
			.usage = orhi::types::EBufferUsageFlags::VERTEX_BUFFER_BIT
		}
	);
	vertexBuffer->Allocate(
		orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT |
		orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT
	);
	vertexBuffer->Upload(k_vertices.data());

	std::unique_ptr<orhi::Buffer> indexBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = sizeof(k_indices),
			.usage = orhi::types::EBufferUsageFlags::INDEX_BUFFER_BIT
		}
	);
	indexBuffer->Allocate(
		orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT |
		orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT
	);
	indexBuffer->Upload(k_indices.data());

	// Load texture data
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load("assets/texture.jpg", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	uint64_t imageSize = texWidth * texHeight * 4;
	if (!pixels)
	{
		throw std::runtime_error("failed to load texture image!");
	}
	const uint32_t mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight))) + 1);

	// Create a buffer to hold the texture data
	std::unique_ptr<orhi::Buffer> pixelBuffer = std::make_unique<orhi::Buffer>(
		device,
		orhi::data::BufferDesc{
			.size = imageSize,
			.usage = orhi::types::EBufferUsageFlags::TRANSFER_SRC_BIT
		}
	);
	pixelBuffer->Allocate(
		orhi::types::EMemoryPropertyFlags::HOST_VISIBLE_BIT |
		orhi::types::EMemoryPropertyFlags::HOST_COHERENT_BIT
	);
	pixelBuffer->Upload(pixels);

	// Free the loaded pixel data after uploading to the buffer
	stbi_image_free(pixels);

	orhi::Texture texture{
		device,
		orhi::data::TextureDesc{
			.extent = {
				static_cast<uint32_t>(texWidth),
				static_cast<uint32_t>(texHeight),
				1
			},
			.format = orhi::types::EFormat::R8G8B8A8_SRGB,
			.usage =
				orhi::types::ETextureUsageFlags::TRANSFER_SRC_BIT | // for mipmap generation
				orhi::types::ETextureUsageFlags::SAMPLED_BIT |
				orhi::types::ETextureUsageFlags::TRANSFER_DST_BIT,
			.mipLevels = mipLevels
		}
	};
	texture.Allocate(
		orhi::types::EMemoryPropertyFlags::DEVICE_LOCAL_BIT
	);

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

	auto descriptorSetLayout = std::make_unique<orhi::DescriptorSetLayout>(
		device,
		std::initializer_list<orhi::data::DescriptorBinding>{
			{
				.binding = 0,
				.type = orhi::types::EDescriptorType::COMBINED_IMAGE_SAMPLER,
				.stageFlags = orhi::types::EShaderStageFlags::FRAGMENT_BIT
			}
		}
	);

	// Create pipeline layout
	orhi::PipelineLayout pipelineLayout{
		device,
		orhi::data::PipelineLayoutDesc<orhi::BackendTraits>{
			.descriptorSetLayouts = std::to_array({std::ref(*descriptorSetLayout)}),
			.pushConstantRanges = {}
		}
	};

	orhi::Pipeline pipeline{
		device,
		orhi::data::GraphicsPipelineDesc<orhi::BackendTraits>{
			.stages = {
				{ orhi::types::EShaderStageFlags::VERTEX_BIT, vertexShader },
				{ orhi::types::EShaderStageFlags::FRAGMENT_BIT, fragmentShader },
			},
			.renderPass = renderPass,
			.pipelineLayout = pipelineLayout,
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
	std::deque<orhi::Framebuffer> framebuffers;
	std::unique_ptr<orhi::SwapChain> swapChain;
	orhi::math::Extent2D windowSize;
	std::vector<SwapImageResources> swapImagesResources;

	auto recreateSwapChain = [&] {
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
			swapImagesResources.emplace_back(
				framebuffers.emplace_back(
					device,
					orhi::data::FramebufferDesc<orhi::BackendTraits>{
						.attachments = {
							swapChain->GetImageDescriptor(i)
						},
						.renderPass = renderPass,
						.extent = windowSize
					}
				),
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
	auto& transferBuffer = commandPool.AllocateCommandBuffers(1).front().get();

	transferBuffer.Begin(orhi::types::ECommandBufferUsageFlags::ONE_TIME_SUBMIT_BIT);

	transferBuffer.TransitionTextureLayout(
		texture,
		orhi::types::ETextureLayout::UNDEFINED,
		orhi::types::ETextureLayout::TRANSFER_DST_OPTIMAL,
		0,
		mipLevels
	);

	transferBuffer.CopyBufferToTexture(*pixelBuffer, texture);

	for (uint32_t i = 1; i < mipLevels; i++)
	{
		const uint32_t srcIndex = i - 1;
		const uint32_t dstIndex = i;

		transferBuffer.TransitionTextureLayout(
			texture,
			orhi::types::ETextureLayout::TRANSFER_DST_OPTIMAL,
			orhi::types::ETextureLayout::TRANSFER_SRC_OPTIMAL,
			srcIndex
		);

		transferBuffer.BlitTexture(
			texture,
			texture,
			// Source region
			orhi::data::TextureRegion{
				.mipLevel = srcIndex,
				.rect = orhi::math::Rect3D{
					.offset = { 0, 0, 0 },
					.extent = {
						static_cast<uint32_t>(texWidth >> (srcIndex)),
						static_cast<uint32_t>(texHeight >> (srcIndex)),
						1
					}
				}
			},
			// Destination region
			orhi::data::TextureRegion{
				.mipLevel = dstIndex,
				.rect = orhi::math::Rect3D{
					.offset = { 0, 0, 0 },
					.extent = {
						static_cast<uint32_t>(texWidth >> i),
						static_cast<uint32_t>(texHeight >> i),
						1
					}
				}
			}
		);

		transferBuffer.TransitionTextureLayout(
			texture,
			orhi::types::ETextureLayout::TRANSFER_SRC_OPTIMAL,
			orhi::types::ETextureLayout::SHADER_READ_ONLY_OPTIMAL,
			srcIndex
		);
	}

	transferBuffer.TransitionTextureLayout(
		texture,
		orhi::types::ETextureLayout::TRANSFER_DST_OPTIMAL,
		orhi::types::ETextureLayout::SHADER_READ_ONLY_OPTIMAL,
		mipLevels - 1
	);
	
	transferBuffer.End();
	device.GetGraphicsAndComputeQueue().Submit({ transferBuffer });
	device.WaitIdle();

	auto textureDescriptor = std::make_unique<orhi::Descriptor>(
		device,
		orhi::data::TextureViewDesc{
			.texture = texture,
			.mipLevels = mipLevels
		}
	);

	auto samplerDescriptor = std::make_unique<orhi::Descriptor>(
		device,
		orhi::data::SamplerDesc{
			.anisotropy = true,
			.mipLodBias = (mipLevels - 1) / 2.0f, // Force median mipmap level to visualize mipmapping
			.minLod = 0.0f,
			.maxLod = static_cast<float>(mipLevels - 1),
		}
	);

	// Create a descriptor pool to allocate descriptor sets
	auto descriptorPool = std::make_unique<orhi::DescriptorPool>(
		device,
		orhi::data::DescriptorPoolDesc{
			.flags = orhi::types::EDescriptorPoolCreateFlags::NONE,
			.maxSets = k_maxFramesInFlight,
			.poolSizes = {
				{ orhi::types::EDescriptorType::COMBINED_IMAGE_SAMPLER, k_maxFramesInFlight }
			}
		}
	);

	// Create a descriptor set for each frame
	auto descriptorSets = descriptorPool->AllocateDescriptorSets(
		*descriptorSetLayout,
		k_maxFramesInFlight
	);

	// Update each descriptor set 
	for (size_t i = 0; i < k_maxFramesInFlight; i++)
	{
		descriptorSets[i].get().Write({
			{
				0,
				{
					orhi::data::TextureSamplerDescriptorWriteInfo{
						.textureDescriptor = *textureDescriptor,
						.samplerDescriptor = *samplerDescriptor
					}
				}
			}
		});
	}

	std::vector<FrameResources> framesResources;
	framesResources.reserve(k_maxFramesInFlight);
	for (uint8_t i = 0; i < k_maxFramesInFlight; ++i)
	{
		framesResources.emplace_back(
			commandBuffers[i],
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
		commandBuffer.BeginRenderPass(
			renderPass,
			swapImageResources.framebuffer,
			windowSize,
			{ orhi::data::ColorClearValue{0.0f, 0.0f, 0.0f, 1.0f} }
		);

		commandBuffer.BindPipeline(orhi::types::EPipelineBindPoint::GRAPHICS, pipeline);

		commandBuffer.BindDescriptorSets(
			std::to_array({ std::ref(frameResources.descriptorSet) }),
			pipelineLayout
		);

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

		commandBuffer.BindVertexBuffers(
			std::to_array({ std::ref(*vertexBuffer) }),
			std::to_array<uint64_t>({ 0 })
		);

		commandBuffer.BindIndexBuffer(
			*indexBuffer
		);

		commandBuffer.DrawIndexed(static_cast<uint32_t>(k_indices.size()));

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
