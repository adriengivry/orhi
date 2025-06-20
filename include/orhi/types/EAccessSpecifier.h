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
	* Defines some access hints that buffers can use
	*/
	enum class EAccessSpecifier : uint8_t
	{
		STREAM_DRAW,
		STREAM_READ,
		STREAM_COPY,
		DYNAMIC_DRAW,
		DYNAMIC_READ,
		DYNAMIC_COPY,
		STATIC_DRAW,
		STATIC_READ,
		STATIC_COPY
	};
}