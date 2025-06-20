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
	* Enumeration of primitive modes
	*/
	enum class EPrimitiveMode : uint8_t
	{
		POINTS,
		LINES,
		LINE_LOOP,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
		LINES_ADJACENCY,
		LINE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY,
		TRIANGLE_STRIP_ADJACENCY,
		PATCHES
	};
}