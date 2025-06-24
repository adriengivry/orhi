/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>

namespace orhi::impl::mock
{
	struct BufferContext
	{
		uint64_t allocatedBytes = 0;
		types::EBufferType type = types::EBufferType::UNKNOWN;
	};

	using Buffer = api::TBuffer<types::EGraphicsBackend::MOCK, BufferContext>;
}
