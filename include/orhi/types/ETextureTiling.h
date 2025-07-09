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
	* Enumeration of available texture tiling modes
	*/
	enum class ETextureTiling : uint8_t
	{
		OPTIMAL,
		LINEAR
	};
}
