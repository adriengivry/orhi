/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <array>

#include <orhi/math/Vec4.h>

namespace orhi::math
{
	struct Mat4
	{
		std::array<Vec4, 4> data {{
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f},
			{0.0f, 0.0f, 0.0f, 0.0f}
		}};

		Vec4& operator[](int index)
		{
			return data[index];
		}

		const Vec4& operator[](int index) const
		{
			return data[index];
		}
	};
}
