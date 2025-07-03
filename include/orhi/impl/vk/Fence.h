/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFence.h>

namespace orhi::impl::vk
{
	struct FenceContext {};
	using Fence = api::TFence<types::EGraphicsBackend::VULKAN, FenceContext>;
}
