/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TPipelineLayout.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

namespace orhi::impl::vk
{
	struct PipelineLayoutContext 
	{
		Device& device;
	};

	using PipelineLayout = api::TPipelineLayout<BackendTraits>;
}
