/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Offset3D.h>
#include <orhi/math/Extent3D.h>

namespace orhi::math
{
	/**
	* @brief 3D rectangle defined by offset and extent
	*
	* Represents a rectangular region in 3D space with a starting position (offset)
	* and size (extent). Commonly used for 3D area specifications.
	*/
	struct Rect3D
	{
		Offset3D offset;
		Extent3D extent;
	};
}
