/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <vector>
#include <unordered_map>

#include <orhi/api/TShaderProgram.h>
#include <orhi/impl/gl/ShaderStage.h>

namespace orhi::impl::gl
{
	struct ShaderProgramContext
	{
		const uint32_t id;
		std::unordered_map<std::string, data::UniformInfo> uniforms;
		std::unordered_map<std::string, uint32_t> uniformsLocationCache;
		std::vector<std::reference_wrapper<const ShaderStage>> attachedShaders;

		uint32_t GetUniformLocation(std::string_view p_name);
	};

	using ShaderProgram = api::TShaderProgram<types::EGraphicsBackend::OPENGL, ShaderProgramContext, ShaderStageContext>;
}
