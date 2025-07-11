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
	* @brief Sample count flags enumeration for multisampling anti-aliasing
	* 
	* Defines the number of samples per pixel used in multisampling
	* anti-aliasing (MSAA) operations. Higher sample counts provide
	* better edge quality at increased memory and performance cost.
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
