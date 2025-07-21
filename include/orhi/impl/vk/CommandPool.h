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

#include <deque>

namespace orhi::impl::vk
{
	struct CommandPoolContext
	{
		Device& device;
		std::deque<CommandBuffer> commandBuffers;
	};

	using CommandPool = api::TCommandPool<BackendTraits>;
}
