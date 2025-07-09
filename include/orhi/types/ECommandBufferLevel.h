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
	* Enumeration of command buffer levels
	*/
	enum class ECommandBufferLevel
	{
		PRIMARY = 0,
		SECONDARY = 1,
	};
}
