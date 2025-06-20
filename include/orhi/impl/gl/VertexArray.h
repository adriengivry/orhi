/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexArray.h>
#include <orhi/impl/gl/IndexBuffer.h>
#include <orhi/impl/gl/VertexBuffer.h>

namespace orhi::impl::gl
{
	struct VertexArrayContext
	{
		uint32_t id = 0;
		uint32_t attributeCount = 0;
	};

	using VertexArray = api::TVertexArray<
		types::EGraphicsBackend::OPENGL,
		VertexArrayContext,
		VertexBufferContext,
		IndexBufferContext,
		BufferContext
	>;
}
