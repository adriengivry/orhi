/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderStorageBuffer.h>
#include <orhi/impl/mock/Buffer.h>

namespace orhi::impl::mock
{
	struct ShaderStorageBufferContext {};
	using ShaderStorageBuffer = api::TShaderStorageBuffer<types::EGraphicsBackend::NONE, ShaderStorageBufferContext, BufferContext>;
}
