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
	* @brief Color component flags enumeration for color write masking
	* 
	* Defines which color components (Red, Green, Blue, Alpha) can be
	* written to during rendering operations. Used to selectively enable
	* or disable writing to specific color channels in framebuffers.
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
