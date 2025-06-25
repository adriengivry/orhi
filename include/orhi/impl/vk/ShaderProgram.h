/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderProgram.h>
#include <orhi/impl/vk/ShaderStage.h>

namespace orhi::impl::vk
{
	struct ShaderProgramContext {};
	using ShaderProgram = api::TShaderProgram<types::EGraphicsBackend::VULKAN, ShaderProgramContext, ShaderStageContext>;
}
