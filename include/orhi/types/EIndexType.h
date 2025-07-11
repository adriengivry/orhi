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
	* @brief Index buffer data type enumeration for indexed rendering
	* 
	* Defines the data types that can be used for index buffers when
	* performing indexed draw operations. Different types provide
	* different ranges and memory usage characteristics.
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
	};
}
