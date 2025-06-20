/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TTextureHandle.h>

namespace orhi::impl::mock
{
	struct TextureHandleContext
	{
		const types::ETextureType type;
	};

	using TextureHandle = api::TTextureHandle<types::EGraphicsBackend::NONE, TextureHandleContext>;
}
