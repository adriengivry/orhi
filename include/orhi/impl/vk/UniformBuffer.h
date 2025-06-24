/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TUniformBuffer.h>
#include <orhi/impl/vk/Buffer.h>

namespace orhi::impl::vk
{
	struct UniformBufferContext {};
	using UniformBuffer = api::TUniformBuffer<types::EGraphicsBackend::VULKAN, UniformBufferContext, BufferContext>;
}
