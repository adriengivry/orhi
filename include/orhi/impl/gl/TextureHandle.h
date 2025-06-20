/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TTextureHandle.h>

namespace orhi::impl::gl
{
	struct TextureHandleContext
	{
		uint32_t id;
		const uint32_t type;
	};

	using TextureHandle = api::TTextureHandle<types::EGraphicsBackend::OPENGL, TextureHandleContext>;
}
