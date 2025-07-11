/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <stdexcept>

namespace orhi::math
{
	/**
	* @brief Three-dimensional floating-point vector structure
	* 
	* Represents a 3D vector with x, y, and z components, commonly used for
	* positions, directions, normals, and colors in 3D graphics programming.
	* Provides array-style access to components for convenient manipulation.
	*/
	struct Vec3
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		/**
		* @brief Provides mutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z)
		* @return Reference to the component at the specified index
		*/
		float& operator[](int index)
		{
			return (&x)[index];
		}

		/**
		* @brief Provides immutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z)
		* @return Const reference to the component at the specified index
		*/
		const float& operator[](int index) const
		{
			return (&x)[index];
		}
	};
}
