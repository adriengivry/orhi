/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderModule.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/ContextRegistry.h>

struct VkShaderModule_T;
typedef VkShaderModule_T* VkShaderModule;

namespace orhi::impl::vk
{
	struct ShaderModuleContext
	{
		Device& device;
		VkShaderModule handle;
	};

	using ShaderModule = api::TShaderModule<types::EGraphicsBackend::VULKAN, ContextRegistry>;
}
