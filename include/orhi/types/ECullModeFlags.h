/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/utils/BitmaskOperators.h>

namespace orhi::types
{
	/**
	* @brief Face culling mode flags enumeration for rasterization
	* 
	* Defines which polygon faces should be culled (discarded) during
	* rasterization based on their winding order. Used to optimize
	* rendering by skipping back-facing or front-facing triangles.
	*/
	enum class ECullModeFlags : uint32_t
	{
		NONE = 0,
		FRONT_BIT = 0x00000001,
		BACK_BIT = 0x00000002,
		FRONT_AND_BACK = 0x00000003,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::ECullModeFlags);
