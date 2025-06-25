/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/IndexBuffer.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	IndexBuffer::TIndexBuffer() : TBuffer(types::EBufferType::INDEX)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
