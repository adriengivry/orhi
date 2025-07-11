/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandPool.h>
#include <orhi/impl/vk/ContextRegistry.h>
#include <orhi/impl/vk/CommandBuffer.h>
#include <orhi/impl/vk/Device.h>

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

	using CommandPool = api::TCommandPool<types::EGraphicsBackend::VULKAN, ContextRegistry>;
}
