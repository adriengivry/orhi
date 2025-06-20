/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_MOCK)

#include <orhi/debug/Assert.h>
#include <orhi/impl/mock/Framebuffer.h>
#include <orhi/impl/mock/Renderbuffer.h>

using namespace orhi::impl::mock;

namespace orhi
{
	template<>
	template<>
	void Framebuffer::Attach(std::shared_ptr<Renderbuffer> p_toAttach, types::EFramebufferAttachment p_attachment, uint32_t p_index, std::optional<uint32_t> p_layer)
	{
		ORHI_ASSERT(p_toAttach != nullptr, "Cannot attach a null renderbuffer");
		ORHI_ASSERT(!p_layer.has_value(), "Renderbuffer cannot use layers");
		const auto index = std::underlying_type_t<types::EFramebufferAttachment>(p_attachment);
		m_context.attachments[index] = p_toAttach;
	}

	template<>
	template<>
	void Framebuffer::Attach(std::shared_ptr<Texture> p_toAttach, types::EFramebufferAttachment p_attachment, uint32_t p_index, std::optional<uint32_t> p_layer)
	{
		ORHI_ASSERT(p_toAttach != nullptr, "Cannot attach a null texture");
		const auto index = std::underlying_type_t<types::EFramebufferAttachment>(p_attachment);
		m_context.attachments[index] = p_toAttach;
	}

	template<>
	Framebuffer::TFramebuffer(std::string_view p_debugName) :
		m_context{ .debugName = std::string{p_debugName} }
	{
	}

	template<>
	Framebuffer::~TFramebuffer()
	{
	}

	template<>
	void Framebuffer::Bind() const
	{
	}

	template<>
	void Framebuffer::Unbind() const
	{
	}

	bool Framebuffer::Validate()
	{
		return m_context.valid = true;
	}

	template<>
	bool Framebuffer::IsValid() const
	{
		return m_context.valid;
	}

	template<>
	template<>
	std::optional<std::reference_wrapper<Texture>> Framebuffer::GetAttachment(orhi::types::EFramebufferAttachment p_attachment, uint32_t p_index) const
	{
		const auto index = std::underlying_type_t<types::EFramebufferAttachment>(p_attachment);

		if (m_context.attachments.contains(index))
		{
			auto attachment = m_context.attachments.at(index);

			if (auto pval = std::get_if<std::shared_ptr<Texture>>(&attachment); pval && *pval)
			{
				return **pval;
			}
		}

		return std::nullopt;
	}

	template<>
	template<>
	std::optional<std::reference_wrapper<Renderbuffer>> Framebuffer::GetAttachment(orhi::types::EFramebufferAttachment p_attachment, uint32_t p_index) const
	{
		const auto index = std::underlying_type_t<types::EFramebufferAttachment>(p_attachment);

		if (m_context.attachments.contains(index))
		{
			auto attachment = m_context.attachments.at(index);

			if (auto pval = std::get_if<std::shared_ptr<Renderbuffer>>(&attachment); pval && *pval)
			{
				return **pval;
			}
		}

		return std::nullopt;
	}

	template<>
	void Framebuffer::Resize(uint16_t p_width, uint16_t p_height)
	{
		ORHI_ASSERT(IsValid(), "Cannot resize an invalid framebuffer");

		for (auto& attachment : m_context.attachments)
		{
			if (const auto pval = std::get_if<std::shared_ptr<Texture>>(&attachment.second); pval && *pval)
			{
				(*pval)->Resize(p_width, p_height);
			}
			else if (const auto* pval = std::get_if<std::shared_ptr<Renderbuffer>>(&attachment.second); pval && *pval)
			{
				(*pval)->Resize(p_width, p_height);
			}
		}
	}

	template<>
	void Framebuffer::SetTargetDrawBuffer(std::optional<uint32_t> p_index)
	{
		ORHI_ASSERT(IsValid(), "Cannot set target draw buffer on an invalid framebuffer");
	}

	template<>
	void Framebuffer::SetTargetReadBuffer(std::optional<uint32_t> p_index)
	{
		ORHI_ASSERT(IsValid(), "Cannot set target read buffer on an invalid framebuffer");
	}

	template<>
	uint32_t Framebuffer::GetID() const
	{
		return 0;
	}

	template<>
	std::pair<uint16_t, uint16_t> Framebuffer::GetSize(types::EFramebufferAttachment p_attachment) const
	{
		return { {}, {} }; // <-- I swear it's not an emoji
	}

	template<>
	void Framebuffer::BlitToBackBuffer(uint16_t p_backBufferWidth, uint16_t p_backBufferHeight) const
	{
		ORHI_ASSERT(IsValid(), "Cannot blit an invalid framebuffer to the back buffer");
	}

	template<>
	void Framebuffer::ReadPixels(
		uint32_t p_x,
		uint32_t p_y,
		uint32_t p_width,
		uint32_t p_height,
		types::EPixelDataFormat p_format,
		types::EPixelDataType p_type,
		void* p_data) const
	{
		ORHI_ASSERT(IsValid(), "Cannot read pixels from an invalid framebuffer");
	}
}

#endif // #if defined(ORHI_COMPILE_MOCK)
