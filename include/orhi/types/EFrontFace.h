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
	* @brief Front face winding order enumeration for rasterization
	* 
	* Defines the vertex winding order that determines which side of
	* a triangle is considered the front face. Used in conjunction with
	* face culling to optimize rendering performance.
	*/
	enum class EFrontFace : uint32_t
	{
		COUNTER_CLOCKWISE = 0,
		CLOCKWISE = 1,
	};
}
