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
	* @brief Graphics backend enumeration for API selection
	* 
	* Defines the available graphics rendering backends that can be used
	* by the ORHI abstraction layer. Each backend provides different
	* performance characteristics and platform support.
	*/
	enum class EGraphicsBackend : uint8_t
	{
		MOCK,
		VULKAN,
		DIRECTX12,
	};
}
