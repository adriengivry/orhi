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
	struct Mat3
	{
		std::array<Vec3, 4> data {{
			{0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f}
		}};

		Vec3& operator[](int index)
		{
			return data[index];
		}

		const Vec3& operator[](int index) const
		{
			return data[index];
		}
	};
}
