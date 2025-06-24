/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TIndexBuffer.h>
#include <orhi/impl/vk/Buffer.h>

namespace orhi::impl::vk
{
	struct IndexBufferContext {};
	using IndexBuffer = api::TIndexBuffer<types::EGraphicsBackend::VULKAN, IndexBufferContext, BufferContext>;
}
