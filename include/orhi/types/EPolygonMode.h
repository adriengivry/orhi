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
	* Polygon mode enumeration for rasterization
	*/
	enum class EPolygonMode : uint32_t
	{
		FILL = 0,
		LINE = 1,
		POINT = 2,
		FILL_RECTANGLE_NV = 1000153000,
	};
}
