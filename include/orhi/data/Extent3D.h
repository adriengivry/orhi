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
	*
	*/
	struct Extent3D
	{
		uint32_t width;
		uint32_t height;
		uint32_t depth;
	};
}
