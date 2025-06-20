/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TIndexBuffer.h>
#include <orhi/impl/gl/Buffer.h>

namespace orhi::impl::gl
{
	struct IndexBufferContext {};
	using IndexBuffer = api::TIndexBuffer<types::EGraphicsBackend::OPENGL, IndexBufferContext, BufferContext>;
}
