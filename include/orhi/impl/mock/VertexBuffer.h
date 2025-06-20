/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexBuffer.h>
#include <orhi/impl/mock/Buffer.h>

namespace orhi::impl::mock
{
	struct VertexBufferContext {};
	using VertexBuffer = api::TVertexBuffer<types::EGraphicsBackend::NONE, VertexBufferContext, BufferContext>;
}
