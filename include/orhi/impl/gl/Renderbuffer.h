/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TRenderbuffer.h>

namespace orhi::impl::gl
{
	struct RenderbufferContext
	{
		uint32_t id = 0;
		uint16_t width = 0;
		uint16_t height = 0;
		types::EInternalFormat format = types::EInternalFormat::RGBA;
		bool allocated = false;
	};

	using Renderbuffer = api::TRenderbuffer<types::EGraphicsBackend::OPENGL, RenderbufferContext>;
}
