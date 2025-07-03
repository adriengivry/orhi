/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSwapChain.h>
#include <orhi/impl/vk/Framebuffer.h>

namespace orhi::impl::vk
{
	struct SwapChainContext {};
	using SwapChain = api::TSwapChain<types::EGraphicsBackend::VULKAN, SwapChainContext, FramebufferContext>;
}
