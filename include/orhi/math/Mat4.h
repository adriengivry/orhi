/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Vec4.h>

#include <array>

namespace orhi::math
{
	/**
	* @brief Four-by-four floating-point matrix structure
	* 
	* Represents a 4x4 matrix composed of four Vec4 columns, the fundamental
	* structure for 3D transformations including translation, rotation, scaling,
	* and projection operations in graphics programming. Provides row-based access.
	*/
	struct Mat4
	{
		std::array<Vec4, 4> data {{
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f}
		}};

		/**
		* @brief Provides mutable access to matrix rows
		* @param index The row index (0-3)
		* @return Reference to the Vec4 row at the specified index
		*/
		Vec4& operator[](int index)
		{
			return data[index];
		}

		/**
		* @brief Provides immutable access to matrix rows
		* @param index The row index (0-3)
		* @return Const reference to the Vec4 row at the specified index
		*/
		const Vec4& operator[](int index) const
		{
			return data[index];
		}
	};
}
