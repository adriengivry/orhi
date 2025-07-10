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
	* Sampler mipmap mode enumeration for mipmap filtering
	*/
	enum class ESamplerMipmapMode : uint32_t
	{
		NEAREST = 0,
		LINEAR = 1
	};
}
