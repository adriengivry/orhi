/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TFramebuffer.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

namespace orhi::impl::dx12
{
	struct FramebufferContext
	{
		Device& device;
	};

	using Framebuffer = api::TFramebuffer<BackendTraits>;
}
