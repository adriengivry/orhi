/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/data/Extent3D.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureUsageType.h>
#include <orhi/types/ETextureType.h>
#include <orhi/types/ETextureTiling.h>
#include <orhi/types/ETextureLayout.h>
#include <orhi/types/ESampleCountFlags.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TTexture.h>

namespace orhi::data
{
	/**
	*
	*/
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	struct TextureViewDesc
	{
		api::TTexture<Backend, ContextRegistry>& texture;
		types::EFormat format = types::EFormat::R8G8B8A8_SRGB;
		types::ETextureType type = types::ETextureType::TEXTURE_2D;
		uint32_t mipLevels = 1;
		uint32_t arrayLayers = 1;
	};
}
