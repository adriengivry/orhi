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
	* @brief Stencil operation enumeration for stencil buffer manipulation
	* 
	* Defines the operations that can be performed on the stencil buffer
	* when stencil testing passes or fails. Controls how stencil values
	* are modified during depth and stencil testing operations.
	*/
	enum class EStencilOp : uint32_t
	{
		KEEP = 0,
		ZERO = 1,
		REPLACE = 2,
		INCREMENT_AND_CLAMP = 3,
		DECREMENT_AND_CLAMP = 4,
		INVERT = 5,
		INCREMENT_AND_WRAP = 6,
		DECREMENT_AND_WRAP = 7,
	};
}
