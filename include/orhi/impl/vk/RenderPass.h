/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TRenderPass.h>
#include <orhi/impl/vk/Device.h>

struct VkRenderPass_T;
typedef VkRenderPass_T* VkRenderPass;

namespace orhi::impl::vk
{
	struct RenderPassContext
	{
		Device& device;
		VkRenderPass handle;
	};

	using RenderPass = api::TRenderPass<types::EGraphicsBackend::VULKAN, CTX_SIG_DEF>;
}
