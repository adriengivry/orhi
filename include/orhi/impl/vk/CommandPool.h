/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandPool.h>
#include <orhi/impl/vk/CommandBuffer.h>

struct VkCommandPool_T;
typedef VkCommandPool_T* VkCommandPool;

namespace orhi::impl::vk
{
	struct CommandPoolContext
	{
		Device& device;
		VkCommandPool handle;
		std::list<CommandBuffer> commandBuffers;
	};

	struct DescriptorContext;

	using CommandPool = api::TCommandPool<
		types::EGraphicsBackend::VULKAN,
		CommandPoolContext,
		DeviceContext,
		CommandBufferContext,
		RenderPassContext,
		FramebufferContext,
		BufferContext,
		DescriptorSetContext,
		TextureContext,
		DescriptorContext
	>;
}
