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
	* 
	*/
	enum class EIndexType
	{
		UINT16 = 0,
		UINT32 = 1,
		UINT8 = 1000265000,
		NONE_KHR = 1000165000,
		NONE_NV = NONE_KHR,
		UINT8_EXT = UINT8,
		UINT8_KHR = UINT8,
		MAX_ENUM = 0x7FFFFFFF
	};
}
