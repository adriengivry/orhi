/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderProgram.h>
#include <orhi/impl/mock/ShaderStage.h>

namespace orhi::impl::mock
{
	struct ShaderProgramContext {};
	using ShaderProgram = api::TShaderProgram<types::EGraphicsBackend::MOCK, ShaderProgramContext, ShaderStageContext>;
}
