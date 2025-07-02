/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TRenderPass.h>

struct VkRenderPass_T;
typedef VkRenderPass_T* VkRenderPass;

namespace orhi::impl::vk
{
	struct RenderPassContext
	{
		VkRenderPass handle;
	};

	using RenderPass = apii::TRenderPass<types::EGraphicsBackend::VULKAN, RenderPassContext>;
}
