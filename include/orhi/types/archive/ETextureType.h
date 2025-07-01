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
	* Enumeration of texture types
	*/
	enum class ETextureType : uint8_t
	{
		TEXTURE_2D,
		TEXTURE_CUBE
	};
}
