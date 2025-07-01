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
	* Enumeration of pixel data formats
	*/
	enum class EPixelDataFormat : uint8_t
	{
		COLOR_INDEX,
		STENCIL_INDEX,
		DEPTH_COMPONENT,
		RED,
		GREEN,
		BLUE,
		ALPHA,
		RGB,
		BGR,
		RGBA,
		BGRA,
		LUMINANCE,
		LUMINANCE_ALPHA,
	};
}
