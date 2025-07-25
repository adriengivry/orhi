/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandPool.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/CommandBuffer.h>
#include <orhi/impl/dx12/Device.h>

#include <deque>

namespace orhi::impl::dx12
{
	struct CommandPoolContext
	{
		Device& device;
		std::deque<CommandBuffer> commandBuffers;
	};

	using CommandPool = api::TCommandPool<BackendTraits>;
}
