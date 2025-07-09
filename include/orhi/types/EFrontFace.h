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
	* Front face enumeration for rasterization
	*/
	enum class EFrontFace : uint32_t
	{
		COUNTER_CLOCKWISE = 0,
		CLOCKWISE = 1,
	};
}
