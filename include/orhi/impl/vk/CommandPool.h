/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TCommandPool.h>

namespace orhi::impl::vk
{
	struct CommandPoolContext {};
	using CommandPool = apii::TCommandPool<types::EGraphicsBackend::VULKAN, CommandPoolContext>;
}
