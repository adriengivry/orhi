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
	* @brief Three-dimensional vector structure
	* 
	* Represents a 3D vector with x, y, and z components, commonly used for
	* positions, directions, normals, and colors in 3D graphics programming.
	* Provides array-style access to components for convenient manipulation.
	*/
	template<typename T>
	struct TVec3
	{
		T x{};
		T y{};
		T z{};

		/**
		* @brief Provides mutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z)
		* @return Reference to the component at the specified index
		*/
		inline float& operator[](int index) { return (&x)[index]; }

		/**
		* @brief Provides immutable array-style access to vector components
		* @param index The component index (0 for x, 1 for y, 2 for z)
		* @return Const reference to the component at the specified index
		*/
		inline const float& operator[](int index) const { return (&x)[index]; }
	};

	using Vec3f = TVec3<float>;
	using Vec3d = TVec3<double>;
	using Vec3u8 = TVec3<uint8_t>;
	using Vec3u16 = TVec3<uint16_t>;
	using Vec3u32 = TVec3<uint32_t>;
	using Vec3u64 = TVec3<uint64_t>;
	using Vec3i8 = TVec3<int8_t>;
	using Vec3i16 = TVec3<int16_t>;
	using Vec3i32 = TVec3<int32_t>;
	using Vec3i64 = TVec3<int64_t>;
}
