/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TTexture.h>
#include <orhi/impl/gl/TextureHandle.h>

namespace orhi::impl::gl
{
	struct TextureContext
	{
		data::TextureDesc desc;
		bool allocated = false;
		std::string debugName;
	};

	using Texture = api::TTexture<types::EGraphicsBackend::OPENGL, TextureContext, TextureHandleContext>;
}
