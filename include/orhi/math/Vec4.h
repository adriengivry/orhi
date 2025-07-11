/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

namespace orhi::math
{
	/**
	* @brief Four-dimensional floating-point vector structure
	* 
	* Represents a 4D vector with x, y, z, and w components, commonly used for
	* homogeneous coordinates, quaternions, RGBA colors, and 4D mathematical
	* operations in graphics programming. Provides array-style access to components.
	*/
	struct Vec4
	{
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		/**
		* @brief Provides mutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z, 3 for w)
		* @return Reference to the component at the specified index
		*/
		float& operator[](int index)
		{
			return (&x)[index];
		}

		/**
		* @brief Provides immutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z, 3 for w)
		* @return Const reference to the component at the specified index
		*/
		const float& operator[](int index) const
		{
			return (&x)[index];
		}
	};
}
