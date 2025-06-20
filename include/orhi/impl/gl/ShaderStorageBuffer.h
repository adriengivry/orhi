/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderStorageBuffer.h>
#include <orhi/impl/gl/Buffer.h>

namespace orhi::impl::gl
{
	struct ShaderStorageBufferContext
	{
		uint32_t id = 0;
	};

	using ShaderStorageBuffer = api::TShaderStorageBuffer<types::EGraphicsBackend::OPENGL, ShaderStorageBufferContext, BufferContext>;
}
