/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/debug/Assert.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/Renderbuffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	Renderbuffer::TRenderbuffer()
	{
		glCreateRenderbuffers(1, &m_context.id);
	}

	template<>
	Renderbuffer::~TRenderbuffer()
	{
		glDeleteRenderbuffers(1, &m_context.id);
	}

	template<>
	void Renderbuffer::Bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_context.id);
	}

	template<>
	void Renderbuffer::Unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	template<>
	uint32_t Renderbuffer::GetID() const
	{
		return m_context.id;
	}

	template<>
	void Renderbuffer::Allocate(uint16_t p_width, uint16_t p_height, types::EInternalFormat p_format)
	{
		m_context.width = p_width;
		m_context.height = p_height;
		m_context.format = p_format;

		glNamedRenderbufferStorage(m_context.id, utils::EnumToValue<GLenum>(m_context.format), m_context.width, m_context.height);

		m_context.allocated = true;
	}

	template<>
	bool Renderbuffer::IsValid() const
	{
		return m_context.allocated;
	}

	template<>
	void Renderbuffer::Resize(uint16_t p_width, uint16_t p_height)
	{
		ORHI_ASSERT(IsValid(), "Cannot resize a renderbuffer that has not been allocated");
		Allocate(p_width, p_height, m_context.format);
	}


	template<>
	uint16_t Renderbuffer::GetWidth() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get width of an invalid renderbuffer");
		return m_context.width;
	}

	template<>
	uint16_t Renderbuffer::GetHeight() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get height of an invalid renderbuffer");
		return m_context.height;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
