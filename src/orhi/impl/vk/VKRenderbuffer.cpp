/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/impl/vk/Renderbuffer.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Renderbuffer::TRenderbuffer()
	{
	}

	template<>
	Renderbuffer::~TRenderbuffer()
	{
	}

	template<>
	void Renderbuffer::Bind() const
	{
	}

	template<>
	void Renderbuffer::Unbind() const
	{
	}

	template<>
	uint32_t Renderbuffer::GetID() const
	{
		return 0;
	}

	template<>
	void Renderbuffer::Allocate(uint16_t p_width, uint16_t p_height, types::EInternalFormat p_format)
	{
		m_context.width = p_width;
		m_context.height = p_height;
		m_context.format = p_format;
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
	}

	template<>
	uint16_t Renderbuffer::GetWidth() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get the height of a renderbuffer that has not been allocated");
		return m_context.width;
	}

	template<>
	uint16_t Renderbuffer::GetHeight() const
	{
		ORHI_ASSERT(IsValid(), "Cannot get the height of a renderbuffer that has not been allocated");
		return m_context.height;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
