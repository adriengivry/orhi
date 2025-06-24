/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/ShaderStorageBuffer.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	ShaderStorageBuffer::TShaderStorageBuffer() : Buffer(types::EBufferType::SHADER_STORAGE)
	{
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
