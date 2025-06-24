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
	* Enumeration of available graphics backends
	*/
	enum class EGraphicsBackend : uint8_t
	{
		MOCK,
		OPENGL
	};
}
