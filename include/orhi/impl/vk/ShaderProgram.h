/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TShaderProgram.h>

namespace orhi::impl::vk
{
	struct ShaderProgramContext {};
	using ShaderProgram = apii::TShaderProgram<types::EGraphicsBackend::VULKAN, ShaderProgramContext>;
}
