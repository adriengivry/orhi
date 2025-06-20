/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>

namespace orhi::impl::gl
{
	struct BufferContext
	{
		uint32_t id = 0;
		types::EBufferType type = types::EBufferType::UNKNOWN;
		uint64_t allocatedBytes = 0;
	};
	
	using Buffer = api::TBuffer<types::EGraphicsBackend::OPENGL, BufferContext>;
}
