/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/impl/mock/IndexBuffer.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	IndexBuffer::TIndexBuffer() : TBuffer(types::EBufferType::INDEX)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
