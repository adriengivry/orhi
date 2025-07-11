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
	* Struct containing the optiomal swap chain description for the current context
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
