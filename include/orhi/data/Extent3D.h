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
	* @brief 3D extent representing width, height, and depth dimensions
	* 
	* Defines the size of a 3D region in terms of width, height, and depth.
	* Commonly used for specifying texture dimensions, render target sizes,
	* and copy operation extents.
	*/
	struct Extent3D
	{
		uint32_t width;
		uint32_t height;
		uint32_t depth;
	};
}
