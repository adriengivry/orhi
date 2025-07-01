/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TSwapChain.h>

namespace orhi::impl::vk
{
	struct SwapChainContext {};
	using SwapChain = apii::TSwapChain<types::EGraphicsBackend::VULKAN, SwapChainContext>;
}
