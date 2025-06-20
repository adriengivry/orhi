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
	* Enumeration of buffer types
	*/
	enum class EBufferType : uint8_t
	{
		VERTEX,
		INDEX,
		UNIFORM,
		SHADER_STORAGE,
		UNKNOWN
	};
}
