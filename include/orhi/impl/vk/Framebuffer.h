/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TFramebuffer.h>

namespace orhi::impl::vk
{
	struct FramebufferContext {};
	using Framebuffer = apii::TFramebuffer<types::EGraphicsBackend::VULKAN, FramebufferContext>;
}
