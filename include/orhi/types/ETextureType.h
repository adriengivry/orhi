/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Texture type enumeration for dimensionality specification
	* 
	* Defines the dimensionality and structure of textures, determining
	* how texture coordinates are interpreted and how data is sampled
	* during rendering operations.
	*/
	enum class ETextureType : uint8_t
	{
		TEXTURE_1D,
		TEXTURE_2D,
		TEXTURE_3D
	};
}
