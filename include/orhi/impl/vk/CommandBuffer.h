/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>

namespace orhi::impl::vk
{
	struct CommandBufferContext {};
	using CommandBuffer = api::TCommandBuffer<types::EGraphicsBackend::VULKAN, CommandBufferContext>;
}
