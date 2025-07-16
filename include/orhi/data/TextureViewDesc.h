/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/impl/common/NativeHandle.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureAspectFlags.h>
#include <orhi/types/ETextureType.h>

namespace orhi::data
{
	/**
	* @brief Descriptor for texture view creation
	* 
	* Defines how a texture should be viewed and accessed by shaders,
	* including the target texture, format interpretation, view type,
	* and mip level and array layer ranges.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	struct TextureViewDesc
	{
		impl::common::NativeHandle texture;
		types::EFormat format = types::EFormat::R8G8B8A8_SRGB;
		types::ETextureType type = types::ETextureType::TEXTURE_2D;
		types::ETextureAspectFlags aspectFlags = types::ETextureAspectFlags::COLOR;
		uint32_t mipLevels = 1;
		uint32_t arrayLayers = 1;
	};
}
