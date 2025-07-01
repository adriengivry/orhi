/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::types
{
	/**
	* Enumeration of uniform types
	*/
	enum class EUniformType : uint8_t
	{
		BOOL,
		INT,
		FLOAT,
		FLOAT_VEC2,
		FLOAT_VEC3,
		FLOAT_VEC4,
		FLOAT_MAT3,
		FLOAT_MAT4,
		DOUBLE_MAT4,
		SAMPLER_2D,
		SAMPLER_CUBE
	};
}
