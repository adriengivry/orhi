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
	* Filter enumeration for texture sampling
	*/
	enum class EFilter : uint32_t
	{
		NEAREST = 0,
		LINEAR = 1
	};
}
