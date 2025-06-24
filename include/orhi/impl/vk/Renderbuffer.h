/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TRenderbuffer.h>

namespace orhi::impl::vk
{
	struct RenderbufferContext
	{
		uint16_t width = 0;
		uint16_t height = 0;
		types::EInternalFormat format = types::EInternalFormat::RGBA;
		bool allocated = false;
	};

	using Renderbuffer = api::TRenderbuffer<types::EGraphicsBackend::VULKAN, RenderbufferContext>;
}
