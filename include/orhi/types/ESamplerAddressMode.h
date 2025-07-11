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
	* @brief Sampler address mode enumeration for texture coordinate handling
	* 
	* Defines how texture coordinates outside the [0,1] range are handled
	* during texture sampling operations. Controls wrapping, clamping,
	* and mirroring behavior for texture coordinate addressing.
	*/
	enum class ESamplerAddressMode : uint32_t
	{
		REPEAT = 0,
		MIRRORED_REPEAT = 1,
		CLAMP_TO_EDGE = 2,
		CLAMP_TO_BORDER = 3,
		MIRROR_CLAMP_TO_EDGE = 4
	};
}
