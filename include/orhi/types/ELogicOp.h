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
	* Logic operation enumeration for color blending
	*/
	enum class ELogicOp : uint32_t
	{
		CLEAR = 0,
		AND = 1,
		AND_REVERSE = 2,
		COPY = 3,
		AND_INVERTED = 4,
		NO_OP = 5,
		XOR = 6,
		OR = 7,
		NOR = 8,
		EQUIVALENT = 9,
		INVERT = 10,
		OR_REVERSE = 11,
		COPY_INVERTED = 12,
		OR_INVERTED = 13,
		NAND = 14,
		SET = 15,
	};
}
