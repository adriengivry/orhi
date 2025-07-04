/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFramebuffer.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/RenderPass.h>

struct VkFramebuffer_T;
typedef VkFramebuffer_T* VkFramebuffer;

namespace orhi::impl::vk
{
	struct FramebufferContext
	{
		Device& device;
		VkFramebuffer handle;
	};

	using Framebuffer = api::TFramebuffer<
		types::EGraphicsBackend::VULKAN,
		FramebufferContext,
		DeviceContext,
		RenderPassContext
	>;
}
