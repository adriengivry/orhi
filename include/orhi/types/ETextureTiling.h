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
	* @brief Texture tiling mode enumeration for memory layout optimization
	* 
	* Defines how texture data is arranged in memory, affecting access
	* patterns and performance characteristics. Optimal tiling provides
	* better performance while linear tiling enables direct CPU access.
	*/
	enum class ETextureTiling : uint8_t
	{
		OPTIMAL,
		LINEAR
	};
}
