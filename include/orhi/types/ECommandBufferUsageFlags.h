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
	* @brief Command buffer usage flags enumeration
	* 
	* Defines how a command buffer will be used, including whether it's
	* submitted only once, continues a render pass, or can be used
	* simultaneously from multiple threads.
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
