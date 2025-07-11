/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Offset2D.h>
#include <orhi/math/Extent2D.h>

namespace orhi::math
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
		Offset2D offset;
		Extent2D extent;
	};
}
