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
	* @brief 3D offset representing X, Y, and Z coordinates
	* 
	* Defines a 3D position or displacement in terms of X, Y, and Z coordinates.
	* Commonly used for specifying starting positions in textures, copy operations,
	* and other 3D spatial operations.
	*/
	struct Offset3D
	{
		int32_t x;
		int32_t y;
		int32_t z;
	};
}
