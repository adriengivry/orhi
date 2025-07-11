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
	template<typename T>
	struct TMat3
	{
		std::array<TVec3<T>, 4> data;

		/**
		* @brief Provides mutable access to matrix rows
		* @param index The row index (0-2)
		* @return Reference to the Vec3 row at the specified index
		*/
		inline TVec3<T>& operator[](int index) { return data[index]; }

		/**
		* @brief Provides immutable access to matrix rows
		* @param index The row index (0-2)
		* @return Const reference to the Vec3 row at the specified index
		*/
		inline const TVec3<T>& operator[](int index) const { return data[index]; }
	};

	using Mat3f = TMat3<float>;
	using Mat3d = TMat3<double>;
	using Mat3u8 = TMat3<uint8_t>;
	using Mat3u16 = TMat3<uint16_t>;
	using Mat3u32 = TMat3<uint32_t>;
	using Mat3u64 = TMat3<uint64_t>;
	using Mat3i8 = TMat3<int8_t>;
	using Mat3i16 = TMat3<int16_t>;
	using Mat3i32 = TMat3<int32_t>;
	using Mat3i64 = TMat3<int64_t>;
}
