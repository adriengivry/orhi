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
	* Sample count enumeration for multisampling
	*/
	enum class ESampleCountFlags : uint32_t
	{
		COUNT_1_BIT = 0x00000001,
		COUNT_2_BIT = 0x00000002,
		COUNT_4_BIT = 0x00000004,
		COUNT_8_BIT = 0x00000008,
		COUNT_16_BIT = 0x00000010,
		COUNT_32_BIT = 0x00000020,
		COUNT_64_BIT = 0x00000040,
	};
}
