/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

namespace orhi::math
{
	/**
	* @brief Two-dimensional floating-point vector structure
	* 
	* Represents a 2D vector with x and y components, commonly used for
	* texture coordinates, screen positions, and 2D mathematical operations
	* in graphics programming. Provides array-style access to components.
	*/
	struct Vec2
	{
		float x = 0.0f;
		float y = 0.0f;

		/**
		* @brief Provides mutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y)
		* @return Reference to the component at the specified index
		*/
		float& operator[](int index)
		{
			return (&x)[index];
		}

		/**
		* @brief Provides immutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y)
		* @return Const reference to the component at the specified index
		*/
		const float& operator[](int index) const
		{
			return (&x)[index];
		}
	};
}
