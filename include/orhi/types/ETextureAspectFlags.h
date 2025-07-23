/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/utils/BitmaskOperators.h>

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Enum representing different aspects of a texture
	* 
	* Texture aspects define the parts of a texture that can be accessed or used.
	*/
	enum class ETextureAspectFlags : uint32_t
	{
		NONE = 0x00000000,
		COLOR = 0x00000001,
		DEPTH = 0x00000002,
		STENCIL = 0x00000004,
		ALL = ~NONE
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::ETextureAspectFlags);
