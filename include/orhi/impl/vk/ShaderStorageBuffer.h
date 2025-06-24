/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TShaderStorageBuffer.h>
#include <orhi/impl/vk/Buffer.h>

namespace orhi::impl::vk
{
	struct ShaderStorageBufferContext {};
	using ShaderStorageBuffer = api::TShaderStorageBuffer<types::EGraphicsBackend::VULKAN, ShaderStorageBufferContext, BufferContext>;
}
