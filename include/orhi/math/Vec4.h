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
	* @brief Four-dimensional vector structure
	* 
	* Represents a 4D vector with x, y, z, and w components, commonly used for
	* homogeneous coordinates, quaternions, RGBA colors, and 4D mathematical
	* operations in graphics programming. Provides array-style access to components.
	*/
	template<typename T>
	struct TVec4
	{
		T x{};
		T y{};
		T z{};
		T w{};

		/**
		* @brief Provides mutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z, 3 for w)
		* @return Reference to the component at the specified index
		*/
		inline T& operator[](int index) { return (&x)[index]; }

		/**
		* @brief Provides immutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z, 3 for w)
		* @return Const reference to the component at the specified index
		*/
		inline const T& operator[](int index) const { return (&x)[index];}
	};

	using Vec4f = TVec4<float>;
	using Vec4d = TVec4<double>;
	using Vec4u8 = TVec4<uint8_t>;
	using Vec4u16 = TVec4<uint16_t>;
	using Vec4u32 = TVec4<uint32_t>;
	using Vec4u64 = TVec4<uint64_t>;
	using Vec4i8 = TVec4<int8_t>;
	using Vec4i16 = TVec4<int16_t>;
	using Vec4i32 = TVec4<int32_t>;
	using Vec4i64 = TVec4<int64_t>;
}
