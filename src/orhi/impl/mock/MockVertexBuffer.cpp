/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/impl/mock/VertexBuffer.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	VertexBuffer::TVertexBuffer() : TBuffer(types::EBufferType::VERTEX)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
