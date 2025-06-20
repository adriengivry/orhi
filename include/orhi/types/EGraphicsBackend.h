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
	* Enumerate graphics backend implementations
	*/
	enum class EGraphicsBackend : uint8_t
	{
		NONE,
		OPENGL
	};
}