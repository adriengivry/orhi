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
	* Enumeration of shader types
	*/
	enum class EShaderType : uint8_t
	{
		NONE,
		VERTEX,
		FRAGMENT,
		GEOMETRY
	};
}
