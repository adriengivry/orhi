/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/Extent3D.h>

#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureType.h>

#include <cstdint>

namespace orhi::api
{
	template<typename BackendTraits> class TTexture;
}

namespace orhi::data
{
	/**
	*
	*/
	template<typename BackendTraits>
	struct TextureViewDesc
	{
		api::TTexture<BackendTraits>& texture;
		types::EFormat format = types::EFormat::R8G8B8A8_SRGB;
		types::ETextureType type = types::ETextureType::TEXTURE_2D;
		uint32_t mipLevels = 1;
		uint32_t arrayLayers = 1;
	};
}
