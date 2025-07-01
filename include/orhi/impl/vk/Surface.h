/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TSurface.h>

namespace orhi::impl::vk
{
	struct SurfaceContext {};
	using Surface = apii::TSurface<types::EGraphicsBackend::VULKAN, SurfaceContext>;
}
