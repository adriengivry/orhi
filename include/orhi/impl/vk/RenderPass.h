/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TRenderPass.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

namespace orhi::impl::vk
{
	struct RenderPassContext
	{
		Device& device;
	};

	using RenderPass = api::TRenderPass<BackendTraits>;
}
