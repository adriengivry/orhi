/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/UniformBuffer.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	UniformBuffer::TUniformBuffer() : Buffer(types::EBufferType::UNIFORM)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
