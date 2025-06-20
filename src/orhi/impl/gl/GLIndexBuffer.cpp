/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/IndexBuffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	IndexBuffer::TIndexBuffer() : TBuffer(types::EBufferType::INDEX)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
