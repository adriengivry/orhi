/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexBuffer.h>
#include <orhi/impl/gl/Buffer.h>

namespace orhi::impl::gl
{
	struct VertexBufferContext{};
	using VertexBuffer = api::TVertexBuffer<types::EGraphicsBackend::OPENGL, VertexBufferContext, BufferContext>;
}
