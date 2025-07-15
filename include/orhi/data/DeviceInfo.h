/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ESampleCountFlags.h>

namespace orhi::data
{
	/**
	* @brief Information about a physical graphics device
	* 
	* Contains identifying information and capabilities of a physical graphics
	* device (GPU) that can be used to create logical devices for rendering operations.
	*/
	struct DeviceInfo
	{
		uint32_t id;
		float maxSamplerAnisotropy;
		types::ESampleCountFlags maxSampleCount;
	};
}
