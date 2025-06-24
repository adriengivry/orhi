/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TTexture.h>
#include <orhi/impl/mock/TextureHandle.h>

namespace orhi::impl::mock
{
	struct TextureContext
	{
		orhi::data::TextureDesc desc;
		bool allocated = false;
		std::string debugName = "";
	};

	using Texture = api::TTexture<types::EGraphicsBackend::MOCK, TextureContext, TextureHandleContext>;
}
