/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/UniformBuffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	UniformBuffer::TUniformBuffer() : Buffer(types::EBufferType::UNIFORM)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
