/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderStage.h>

namespace orhi::impl::mock
{
	struct ShaderStageContext {};
	using ShaderStage = api::TShaderStage<types::EGraphicsBackend::NONE, ShaderStageContext>;
}
