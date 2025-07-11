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
	* @brief Polygon rasterization mode enumeration
	* 
	* Defines how polygons are rasterized during the rendering pipeline,
	* including filled polygons, wireframe rendering, and point rendering.
	* Used to control the visual representation of geometric primitives.
	*/
	enum class EPolygonMode : uint32_t
	{
		FILL = 0,
		LINE = 1,
		POINT = 2,
		FILL_RECTANGLE_NV = 1000153000,
	};
}
