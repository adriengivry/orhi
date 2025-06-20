/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TUniformBuffer.h>
#include <orhi/impl/gl/Buffer.h>

namespace orhi::impl::gl
{
	struct UniformBufferContext {};
	using UniformBuffer = api::TUniformBuffer<types::EGraphicsBackend::OPENGL, UniformBufferContext, BufferContext>;
}
