/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/ShaderStorageBuffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	ShaderStorageBuffer::TShaderStorageBuffer() : Buffer(types::EBufferType::SHADER_STORAGE)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
