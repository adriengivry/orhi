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
	* Enumeration of framebuffer attachment types
	*/
	enum class EFramebufferAttachment : uint8_t
	{
		COLOR,
		DEPTH,
		STENCIL,
		DEPTH_STENCIL
	};
}
