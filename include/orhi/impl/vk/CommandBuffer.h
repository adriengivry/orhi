/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>
#include <orhi/impl/vk/ContextRegistry.h>

struct VkCommandBuffer_T;
typedef VkCommandBuffer_T* VkCommandBuffer;

#define BACKEND_TYPE_REGISTRY struct struct Buffer, struct CommandBuffer, struct CommandPool, struct Descriptor, struct DescriptorPool, struct DescriptorSet, struct DescriptorSetLayout, struct Device, struct Fence, struct Framebuffer, struct GraphicsPipeline, struct Queue, struct RenderPass, struct Semaphore, struct ShaderModule, struct SwapChain, struct Texture

namespace orhi::impl::vk
{
	struct CommandBufferContext
	{
		VkCommandBuffer handle;
	};

	using CommandBuffer = api::TCommandBuffer<ContextRegistry>;
}
