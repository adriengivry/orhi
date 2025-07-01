/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TCommandBuffer.h>

namespace orhi::impl::vk
{
	struct CommandBufferContext {};
	using CommandBuffer = apii::TCommandBuffer<types::EGraphicsBackend::VULKAN, CommandBufferContext>;
}
