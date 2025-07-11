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
	* Enumeration of surface transform flags
	*/
	enum class ESurfaceTransformFlags : uint32_t
	{
		NONE = 0,
		IDENTITY_BIT_KHR = 0x00000001,
		ROTATE_90_BIT_KHR = 0x00000002,
		ROTATE_180_BIT_KHR = 0x00000004,
		ROTATE_270_BIT_KHR = 0x00000008,
		HORIZONTAL_MIRROR_BIT_KHR = 0x00000010,
		HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR = 0x00000020,
		HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR = 0x00000040,
		HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR = 0x00000080,
		INHERIT_BIT_KHR = 0x00000100,
		ALL = ~NONE,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::ESurfaceTransformFlags);
