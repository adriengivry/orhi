/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TShaderModule.h>
#include <orhi/impl/vk/Device.h>

struct VkShaderModule_T;
typedef VkShaderModule_T* VkShaderModule;

namespace orhi::impl::vk
{
	struct ShaderModuleContext
	{
		Device& device;
		VkShaderModule handle;
	};

	using ShaderModule = apii::TShaderModule<types::EGraphicsBackend::VULKAN, ShaderModuleContext, DeviceContext>;
}
