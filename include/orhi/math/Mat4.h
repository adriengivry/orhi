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
	template<typename T>
	struct TMat4
	{
		std::array<TVec4<T>, 4> data;

		/**
		* @brief Provides mutable access to matrix rows
		* @param index The row index (0-3)
		* @return Reference to the Vec4 row at the specified index
		*/
		inline TVec4<T>& operator[](int index) { return data[index]; }

		/**
		* @brief Provides immutable access to matrix rows
		* @param index The row index (0-3)
		* @return Const reference to the Vec4 row at the specified index
		*/
		inline const TVec4<T>& operator[](int index) const { return data[index]; }
	};

	using Mat4f = TMat4<float>;
	using Mat4d = TMat4<double>;
	using Mat4u8 = TMat4<uint8_t>;
	using Mat4u16 = TMat4<uint16_t>;
	using Mat4u32 = TMat4<uint32_t>;
	using Mat4u64 = TMat4<uint64_t>;
	using Mat4i8 = TMat4<int8_t>;
	using Mat4i16 = TMat4<int16_t>;
	using Mat4i32 = TMat4<int32_t>;
	using Mat4i64 = TMat4<int64_t>;
}
