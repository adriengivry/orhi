/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFramebuffer.h>

namespace orhi::impl::vk
{
	struct FramebufferContext {};
	using Framebuffer = api::TFramebuffer<types::EGraphicsBackend::VULKAN, FramebufferContext>;
}
