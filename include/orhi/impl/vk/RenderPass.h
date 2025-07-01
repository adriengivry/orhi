/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TRenderPass.h>

namespace orhi::impl::vk
{
	struct RenderPassContext {};
	using RenderPass = apii::TRenderPass<types::EGraphicsBackend::VULKAN, RenderPassContext>;
}
