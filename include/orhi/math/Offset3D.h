/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Vec3.h>

namespace orhi::math
{
	/**
	* @brief 3D offset representing X, Y, and Z coordinates
	* 
	* Defines a 3D position or displacement in terms of X, Y, and Z coordinates.
	* Commonly used for specifying starting positions in textures, copy operations,
	* and other 3D spatial operations.
	*/
	using Offset3D = Vec3i32;
}
