/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/utils/BitmaskOperators.h>

namespace orhi::types
{
	/**
	* Color component flags enumeration for color blending
	*/
	enum class EColorComponentFlags : uint32_t
	{
		NONE = 0,
		R_BIT = 0x00000001,
		G_BIT = 0x00000002,
		B_BIT = 0x00000004,
		A_BIT = 0x00000008,
		ALL = R_BIT | G_BIT | B_BIT | A_BIT,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::EColorComponentFlags);
