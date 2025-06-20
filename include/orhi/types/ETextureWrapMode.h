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
	* Enumeration of texture wrap modes
	*/
	enum class ETextureWrapMode : uint8_t
	{
		REPEAT,
		CLAMP_TO_EDGE,
		CLAMP_TO_BORDER,
		MIRRORED_REPEAT,
		MIRROR_CLAMP_TO_EDGE
	};
}