/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexArray.h>
#include <orhi/impl/vk/IndexBuffer.h>
#include <orhi/impl/vk/VertexBuffer.h>

namespace orhi::impl::vk
{
	struct VertexArrayContext
	{
		uint32_t attributeCount = 0;
	};

	using VertexArray = api::TVertexArray<
		types::EGraphicsBackend::VULKAN,
		VertexArrayContext,
		VertexBufferContext,
		IndexBufferContext,
		BufferContext
	>;
}
