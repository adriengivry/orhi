/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TShaderModule.h>

namespace orhi::impl::vk
{
	struct ShaderModuleContext {};
	using ShaderModule = apii::TShaderModule<types::EGraphicsBackend::VULKAN, ShaderModuleContext>;
}
