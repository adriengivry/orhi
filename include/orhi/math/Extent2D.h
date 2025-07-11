/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <tuple>

namespace orhi::math
{
	/**
	* @brief 2D extent representing width and height dimensions
	*
	* Defines the size of a 2D region in terms of width and height.
	* Commonly used for specifying texture dimensions, render target sizes,
	* and copy operation extents.
	*/
	struct Extent2D
	{
		uint32_t width;
		uint32_t height;
	};
}
