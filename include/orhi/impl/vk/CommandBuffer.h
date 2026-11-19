/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>
#include <orhi/impl/vk/BackendTraits.h>

#include <vulkan/vulkan.h>

namespace orhi::impl::vk
{
	struct FramebufferContext;

	struct CommandBufferContext
	{
		PFN_vkCmdBeginRenderingKHR beginRendering = nullptr;
		PFN_vkCmdEndRenderingKHR endRendering = nullptr;
		const FramebufferContext* activeFramebuffer = nullptr;
	};

	using CommandBuffer = api::TCommandBuffer<BackendTraits>;
}
