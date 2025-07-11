/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Vec3.h>

#include <array>

namespace orhi::math
{
	/**
	* @brief Three-by-three floating-point matrix structure
	* 
	* Represents a 3x3 matrix composed of three Vec3 columns, commonly used for
	* 2D transformations, 3D rotations, scaling operations, and normal transformations
	* in graphics programming. Provides row-based access through array notation.
	*/
	struct Mat3
	{
		std::array<Vec3, 4> data {{
			{0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f}
		}};

		/**
		* @brief Provides mutable access to matrix rows
		* @param index The row index (0-2)
		* @return Reference to the Vec3 row at the specified index
		*/
		Vec3& operator[](int index)
		{
			return data[index];
		}

		/**
		* @brief Provides immutable access to matrix rows
		* @param index The row index (0-2)
		* @return Const reference to the Vec3 row at the specified index
		*/
		const Vec3& operator[](int index) const
		{
			return data[index];
		}
	};
}
