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
	* Enumeration of buffer usage
	*/
	enum class ECommandBufferUsageFlags : uint32_t
	{
		NONE = 0,
		ONE_TIME_SUBMIT_BIT = 0x00000001,
		RENDER_PASS_CONTINUE_BIT = 0x00000002,
		SIMULTANEOUS_USE_BIT = 0x00000004,
		ALL = ~NONE,
	};
}

ENABLE_BITMASK_OPERATORS(orhi::types::ECommandBufferUsageFlags);
