/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>

namespace orhi::impl::vk
{
	struct BufferContext {};
	using Buffer = api::TBuffer<types::EGraphicsBackend::VULKAN, BufferContext>;
}
