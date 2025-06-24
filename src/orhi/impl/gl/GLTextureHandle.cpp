/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/TextureHandle.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	TextureHandle::TTextureHandle(types::ETextureType p_type) : m_context{
		.type = utils::EnumToValue<GLenum>(p_type)
	}
	{
	}

	template<>
	TextureHandle::TTextureHandle(types::ETextureType p_type, uint32_t p_id) : m_context{
		.id = p_id,
		.type = utils::EnumToValue<GLenum>(p_type)
	}
	{
	}

	template<>
	void TextureHandle::Bind(std::optional<uint32_t> p_slot) const
	{
		if (p_slot.has_value())
		{
			glBindTextureUnit(p_slot.value(), m_context.id);
		}
		else
		{
			glBindTexture(m_context.type, m_context.id);
		}
	}

	template<>
	void TextureHandle::Unbind() const
	{
		glBindTexture(m_context.type, 0);
	}

	template<>
	uint32_t TextureHandle::GetID() const
	{
		return m_context.id;
	}

	template<>
	types::ETextureType TextureHandle::GetType() const
	{
		return utils::ValueToEnum<types::ETextureType>(m_context.type);
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
