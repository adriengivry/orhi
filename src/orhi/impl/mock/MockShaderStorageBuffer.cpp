/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/impl/mock/ShaderStorageBuffer.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	ShaderStorageBuffer::TShaderStorageBuffer() : Buffer(types::EBufferType::SHADER_STORAGE)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
