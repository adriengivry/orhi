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
	* @brief Sampler mipmap mode enumeration for mipmap level filtering
	* 
	* Defines how mipmap levels are selected and interpolated during
	* texture sampling operations. Controls the filtering method used
	* between different mipmap levels for level-of-detail sampling.
	*/
	enum class ESamplerMipmapMode : uint32_t
	{
		NEAREST = 0,
		LINEAR = 1
	};
}
