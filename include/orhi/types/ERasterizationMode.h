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
	* Enumeration of rasterization modes
	*/
	enum class ERasterizationMode : uint8_t
	{
		POINT,
		LINE,
		FILL
	};
}
