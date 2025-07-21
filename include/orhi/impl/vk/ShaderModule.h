/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderModule.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

namespace orhi::impl::vk
{
	struct ShaderModuleContext
	{
		Device& device;
	};

	using ShaderModule = api::TShaderModule<BackendTraits>;
}
