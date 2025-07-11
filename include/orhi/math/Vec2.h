/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::math
{
	/**
	* @brief Two-dimensional floating-point vector structure
	* 
	* Represents a 2D vector with x and y components, commonly used for
	* texture coordinates, screen positions, and 2D mathematical operations
	* in graphics programming. Provides array-style access to components.
	*/
	template<typename T>
	struct TVec2
	{
		T x{};
		T y{};

		/**
		* @brief Provides mutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y)
		* @return Reference to the component at the specified index
		*/
		inline T& operator[](int index) { return (&x)[index]; }

		/**
		* @brief Provides immutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y)
		* @return Const reference to the component at the specified index
		*/
		inline const T& operator[](int index) const { return (&x)[index]; }
	};

	using Vec2f = TVec2<float>;
	using Vec2d = TVec2<double>;
	using Vec2u8 = TVec2<uint8_t>;
	using Vec2u16 = TVec2<uint16_t>;
	using Vec2u32 = TVec2<uint32_t>;
	using Vec2u64 = TVec2<uint64_t>;
	using Vec2i8 = TVec2<int8_t>;
	using Vec2i16 = TVec2<int16_t>;
	using Vec2i32 = TVec2<int32_t>;
	using Vec2i64 = TVec2<int64_t>;
}
