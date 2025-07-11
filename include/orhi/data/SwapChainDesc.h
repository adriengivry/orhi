/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EColorSpace.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/EPresentMode.h>
#include <orhi/types/ESurfaceTransformFlags.h>

#include <cstdint>

namespace orhi::data
{
	/**
	* @brief Optimal swap chain configuration descriptor
	* 
	* Contains the optimal swap chain properties for the current graphics context,
	* including surface format, color space, presentation mode, and image counts.
	* Used to create swap chains with optimal performance and compatibility.
	*/
	struct SwapChainDesc
	{
		types::EFormat format;
		types::EColorSpace colorSpace;
		types::EPresentMode presentMode;
		types::ESurfaceTransformFlags currentTransform;
		uint32_t minImageCount;
		uint32_t maxImageCount;
	};
}
