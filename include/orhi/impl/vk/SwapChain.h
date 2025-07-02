/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TSwapChain.h>
#include <orhi/impl/vk/Framebuffer.h>

namespace orhi::impl::vk
{
	struct SwapChainContext {};
	using SwapChain = apii::TSwapChain<types::EGraphicsBackend::VULKAN, SwapChainContext, FramebufferContext>;
}
