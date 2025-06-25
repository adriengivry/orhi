/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/TextureHandle.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	TextureHandle::TTextureHandle(types::ETextureType p_type) : m_context{
		.type = p_type,
	}
	{
	}

	template<>
	TextureHandle::TTextureHandle(types::ETextureType p_type, uint32_t p_id) : TTextureHandle(p_type)
	{
	}

	template<>
	void TextureHandle::Bind(std::optional<uint32_t> p_slot) const
	{
	}

	template<>
	void TextureHandle::Unbind() const
	{
	}

	template<>
	uint32_t TextureHandle::GetID() const
	{
		return 0;
	}

	template<>
	types::ETextureType TextureHandle::GetType() const
	{
		return m_context.type;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
