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
	struct Rect2D
	{
		std::pair<int32_t, int32_t> offset;
		std::pair<uint32_t, uint32_t> extent;
	};
}
