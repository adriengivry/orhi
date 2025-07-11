/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/Extent3D.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ESampleCountFlags.h>
#include <orhi/types/ETextureTiling.h>
#include <orhi/types/ETextureType.h>
#include <orhi/types/ETextureUsageType.h>
#include <orhi/types/ETextureLayout.h>

#include <cstdint>

namespace orhi::data
{
	/**
	*
	*/
	struct TextureDesc
	{
		Extent3D extent;
		types::EFormat format = types::EFormat::R8G8B8A8_SRGB;
		types::ETextureType type = types::ETextureType::TEXTURE_2D;
		types::ETextureTiling tiling = types::ETextureTiling::OPTIMAL;
		types::ETextureLayout initialLayout = types::ETextureLayout::UNDEFINED;
		types::ETextureUsageFlags usage = types::ETextureUsageFlags::NONE;
		types::ESampleCountFlags samples = types::ESampleCountFlags::COUNT_1_BIT;
		uint32_t mipLevels = 1;
		uint32_t arrayLayers = 1;
	};
}
