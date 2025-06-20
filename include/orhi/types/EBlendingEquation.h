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
	* Blending equations used by the blending operations
	*/
	enum class EBlendingEquation : uint8_t
	{
		FUNC_ADD,
		FUNC_SUBTRACT,
		FUNC_REVERSE_SUBTRACT,
		MIN,
		MAX
	};
}
