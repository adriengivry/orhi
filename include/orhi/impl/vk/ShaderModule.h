/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderModule.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

struct VkShaderModule_T;
typedef VkShaderModule_T* VkShaderModule;

namespace orhi::impl::vk
{
	struct ShaderModuleContext
	{
		Device& device;
	};

	using ShaderModule = api::TShaderModule<BackendTraits>;
}
