/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/impl/gl/VertexBuffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	VertexBuffer::TVertexBuffer() : TBuffer(types::EBufferType::VERTEX)
	{
	}
}

#endif // defined(ORHI_COMPILE_OPENGL)
