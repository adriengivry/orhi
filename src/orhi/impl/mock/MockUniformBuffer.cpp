/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/impl/mock/UniformBuffer.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	UniformBuffer::TUniformBuffer() : Buffer(types::EBufferType::UNIFORM)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
