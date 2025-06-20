/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderStage.h>

namespace orhi::impl::gl
{
	struct ShaderStageContext
	{
		uint32_t id;
		types::EShaderType type;
	};

	using ShaderStage = api::TShaderStage<types::EGraphicsBackend::OPENGL, ShaderStageContext>;
}
