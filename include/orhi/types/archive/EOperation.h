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
	* Graphics operation types for stencil/depth operations
	*/
	enum class EOperation : uint8_t
	{
		ZERO,
		KEEP,
		REPLACE,
		INCREMENT,
		INCREMENT_WRAP,
		DECREMENT,
		DECREMENT_WRAP,
		INVERT
	};
}
