/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Rect3D.h>
#include <orhi/types/ETextureAspectFlags.h>

#include <optional>

namespace orhi::data
{
	/**
	* @brief Descriptor for a texture region
	* 
	* Defines a specific region of a texture, including the aspect flags,
	* mip level, base array layer, and layer count. This is used for
	* texture operations that require specifying a sub-region.
	*/
	struct TextureRegion
	{
		types::ETextureAspectFlags aspectMask = types::ETextureAspectFlags::COLOR;
		uint32_t mipLevel = 1;
		uint32_t baseArrayLayer = 0;
		uint32_t layerCount = 1;
		std::optional<math::Rect3D> rect = std::nullopt;
	};
}
