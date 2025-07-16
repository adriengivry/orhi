/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandPool.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/CommandBuffer.h>
#include <orhi/impl/vk/Device.h>

#include <list>

struct VkCommandPool_T;
typedef VkCommandPool_T* VkCommandPool;

namespace orhi::impl::vk
{
	struct CommandPoolContext
	{
		Device& device;
		std::list<CommandBuffer> commandBuffers;
	};

	using CommandPool = api::TCommandPool<BackendTraits>;
}
