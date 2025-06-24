/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TIndexBuffer.h>
#include <orhi/impl/mock/Buffer.h>

namespace orhi::impl::mock
{
	struct IndexBufferContext {};
	using IndexBuffer = api::TIndexBuffer<types::EGraphicsBackend::MOCK, IndexBufferContext, BufferContext>;
}
