/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TVertexBuffer.h>
#include <orhi/impl/vk/Buffer.h>

namespace orhi::impl::vk
{
	struct VertexBufferContext {};
	using VertexBuffer = api::TVertexBuffer<types::EGraphicsBackend::VULKAN, VertexBufferContext, BufferContext>;
}
