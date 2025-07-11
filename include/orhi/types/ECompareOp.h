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
	* @brief Comparison operation enumeration for depth and stencil testing
	* 
	* Defines the comparison functions used in depth testing, stencil testing,
	* and sampler comparison operations. Determines whether a fragment passes
	* or fails the comparison test.
	*/
	enum class ECompareOp : uint32_t
	{
		NEVER = 0,
		LESS = 1,
		EQUAL = 2,
		LESS_OR_EQUAL = 3,
		GREATER = 4,
		NOT_EQUAL = 5,
		GREATER_OR_EQUAL = 6,
		ALWAYS = 7,
	};
}
