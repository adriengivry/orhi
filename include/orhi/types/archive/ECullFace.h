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
	* Enumeration of cullable face
	*/
	enum class ECullFace : uint8_t
	{
		FRONT,
		BACK,
		FRONT_AND_BACK
	};
}
