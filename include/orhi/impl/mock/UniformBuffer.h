/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TUniformBuffer.h>
#include <orhi/impl/mock/Buffer.h>

namespace orhi::impl::mock
{
	struct UniformBufferContext {};
	using UniformBuffer = api::TUniformBuffer<types::EGraphicsBackend::MOCK, UniformBufferContext, BufferContext>;
}
