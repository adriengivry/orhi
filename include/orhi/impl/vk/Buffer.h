/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TBuffer.h>

namespace orhi::impl::vk
{
	struct BufferContext {};
	using Buffer = apii::TBuffer<types::EGraphicsBackend::VULKAN, BufferContext>;
}
