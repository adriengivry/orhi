/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TFence.h>

namespace orhi::impl::vk
{
	struct FenceContext {};
	using Fence = apii::TFence<types::EGraphicsBackend::VULKAN, FenceContext>;
}
