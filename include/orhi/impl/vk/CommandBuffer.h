/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>
#include <orhi/impl/vk/BackendTraits.h>

namespace orhi::impl::vk
{
	struct CommandBufferContext {};
	using CommandBuffer = api::TCommandBuffer<BackendTraits>;
}
