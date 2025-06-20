/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexArray.h>
#include <orhi/impl/mock/IndexBuffer.h>
#include <orhi/impl/mock/VertexBuffer.h>

namespace orhi::impl::mock
{
	struct VertexArrayContext
	{
		uint32_t attributeCount = 0;
	};

	using VertexArray = api::TVertexArray<
		types::EGraphicsBackend::NONE,
		VertexArrayContext,
		VertexBufferContext,
		IndexBufferContext,
		BufferContext
	>;
}
