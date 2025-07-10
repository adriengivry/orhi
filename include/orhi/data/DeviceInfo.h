/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::data
{
	/**
	* Struct containing information about a physical device
	*/
	struct DeviceInfo
	{
		uint32_t id;
		float maxSamplerAnisotropy;
	};
}
