/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ETextureFilteringMode.h>
#include <orhi/types/ETextureWrapMode.h>
#include <orhi/types/EInternalFormat.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EPixelDataType.h>

namespace orhi::data
{
	/**
	* Structure that holds additional data for mutable textures
	*/
	struct MutableTextureDesc
	{
		types::EFormat format = types::EFormat::RGBA;
		types::EPixelDataType type = types::EPixelDataType::UNSIGNED_BYTE;
		const void* data = nullptr;
	};

	/**
	* Structure that holds the description of a texture
	*/
	struct TextureDesc
	{
		uint32_t width = 0;
		uint32_t height = 0;
		types::ETextureFilteringMode minFilter = types::ETextureFilteringMode::LINEAR_MIPMAP_LINEAR;
		types::ETextureFilteringMode magFilter = types::ETextureFilteringMode::LINEAR;
		types::ETextureWrapMode horizontalWrap = types::ETextureWrapMode::REPEAT;
		types::ETextureWrapMode verticalWrap = types::ETextureWrapMode::REPEAT;
		types::EInternalFormat internalFormat = types::EInternalFormat::RGBA;
		bool useMipMaps = true;
		std::optional<MutableTextureDesc> mutableDesc = std::nullopt;
	};
}
