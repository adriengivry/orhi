/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/VertexBuffer.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	VertexBuffer::TVertexBuffer() : TBuffer(types::EBufferType::VERTEX)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
