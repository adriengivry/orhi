/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <tuple>

namespace orhi::data
{
	/**
	* @brief 2D rectangle defined by offset and extent
	* 
	* Represents a rectangular region in 2D space with a starting position (offset)
	* and size (extent). Commonly used for scissor rectangles, viewport regions,
	* and other 2D area specifications.
	*/
	struct Rect2D
	{
		std::pair<int32_t, int32_t> offset;
		std::pair<uint32_t, uint32_t> extent;
	};
}
