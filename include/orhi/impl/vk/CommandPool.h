/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandPool.h>

namespace orhi::impl::vk
{
	struct CommandPoolContext {};
	using CommandPool = api::TCommandPool<types::EGraphicsBackend::VULKAN, CommandPoolContext>;
}
