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
	* @brief Texture filtering mode enumeration for sampling operations
	* 
	* Defines how texture samples are filtered when the texture is magnified
	* or minified. Controls the interpolation method used between texels
	* to produce the final sampled color value.
	*/
	enum class EFilter : uint32_t
	{
		NEAREST = 0,
		LINEAR = 1
	};
}
