/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_OPENGL)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/gl/details/glad/glad.h>
#include <orhi/impl/gl/details/Types.h>
#include <orhi/impl/gl/Framebuffer.h>
#include <orhi/impl/gl/Renderbuffer.h>

using namespace orhi::impl::gl;

namespace orhi
{
	template<>
	template<>
	void Framebuffer::Attach(
		std::shared_ptr<Renderbuffer> p_toAttach,
		types::EFramebufferAttachment p_attachment,
		uint32_t p_index,
		std::optional<uint32_t> p_layer
	)
	{
		ORHI_ASSERT(p_toAttach != nullptr, "Cannot attach a null renderbuffer");
		ORHI_ASSERT(!p_layer.has_value(), "Renderbuffer cannot use layers");

		const auto attachmentIndex = details::EnumToValue<GLenum>(p_attachment) + static_cast<GLenum>(p_index);
		glNamedFramebufferRenderbuffer(m_context.id, attachmentIndex, GL_RENDERBUFFER, p_toAttach->GetID());
		m_context.attachments[attachmentIndex] = p_toAttach;
	}

	template<>
	template<>
	void Framebuffer::Attach(
		std::shared_ptr<Texture> p_toAttach,
		types::EFramebufferAttachment p_attachment,
		uint32_t p_index,
		std::optional<uint32_t> p_layer
	)
	{
		ORHI_ASSERT(p_toAttach != nullptr, "Cannot attach a null texture");

		const auto attachmentIndex = details::EnumToValue<GLenum>(p_attachment) + static_cast<GLenum>(p_index);
		constexpr uint32_t kMipMapLevel = 0;

		if (p_layer.has_value())
		{
			glNamedFramebufferTextureLayer(m_context.id, attachmentIndex, p_toAttach->GetID(), kMipMapLevel, p_layer.value());
		}
		else
		{
			glNamedFramebufferTexture(m_context.id, attachmentIndex, p_toAttach->GetID(), kMipMapLevel);
		}

		m_context.attachments[attachmentIndex] = p_toAttach;
	}

	template<>
	Framebuffer::TFramebuffer(std::string_view p_debugName) :
		m_context{ .debugName = std::string{p_debugName} }
	{
		glCreateFramebuffers(1, &m_context.id);
	}

	template<>
	Framebuffer::~TFramebuffer()
	{
		glDeleteFramebuffers(1, &m_context.id);
	}

	template<>
	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_context.id);
	}

	template<>
	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	bool Framebuffer::Validate()
	{
		const GLenum status = glCheckNamedFramebufferStatus(m_context.id, GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			ORHI_LOG_ERROR("Framebuffer validation failed with status: " + std::to_string(status));
			return m_context.valid = false;
		}

		return m_context.valid = true;
	}

	template<>
	bool Framebuffer::IsValid() const
	{
		return m_context.valid;
	}

	template<>
	template<>
	std::optional<std::reference_wrapper<Texture>> Framebuffer::GetAttachment(
		orhi::types::EFramebufferAttachment p_attachment,
		uint32_t p_index
	) const
	{
		const auto attachmentIndex = details::EnumToValue<GLenum>(p_attachment) + static_cast<GLenum>(p_index);

		if (m_context.attachments.contains(attachmentIndex))
		{
			auto attachment = m_context.attachments.at(attachmentIndex);

			if (auto pval = std::get_if<std::shared_ptr<Texture>>(&attachment); pval && *pval)
			{
				return **pval;
			}
		}

		return std::nullopt;
	}

	template<>
	template<>
	std::optional<std::reference_wrapper<Renderbuffer>> Framebuffer::GetAttachment(
		orhi::types::EFramebufferAttachment p_attachment,
		uint32_t p_index
	) const
	{
		const auto attachmentIndex = details::EnumToValue<GLenum>(p_attachment) + static_cast<GLenum>(p_index);

		if (m_context.attachments.contains(attachmentIndex))
		{
			auto attachment = m_context.attachments.at(attachmentIndex);

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
		ORHI_ASSERT(IsValid(), "Invalid framebuffer");

		if (p_index.has_value())
		{
			glNamedFramebufferDrawBuffer(m_context.id, GL_COLOR_ATTACHMENT0 + p_index.value());
		}
		else
		{
			glNamedFramebufferDrawBuffer(m_context.id, GL_NONE);
		}
	}

	template<>
	void Framebuffer::SetTargetReadBuffer(std::optional<uint32_t> p_index)
	{
		ORHI_ASSERT(IsValid(), "Invalid framebuffer");

		if (p_index.has_value())
		{
			glNamedFramebufferReadBuffer(m_context.id, GL_COLOR_ATTACHMENT0 + p_index.value());
		}
		else
		{
			glNamedFramebufferReadBuffer(m_context.id, GL_NONE);
		}
	}

	template<>
	uint32_t Framebuffer::GetID() const
	{
		return m_context.id;
	}

	template<>
	std::pair<uint16_t, uint16_t> Framebuffer::GetSize(
		types::EFramebufferAttachment p_attachment
	) const
	{
		ORHI_ASSERT(IsValid(), "Cannot get width of an invalid framebuffer");

		for (auto& attachment : m_context.attachments)
		{
			if (const auto pval = std::get_if<std::shared_ptr<Texture>>(&attachment.second); pval && *pval)
			{
				return {
					(*pval)->GetDesc().width,
					(*pval)->GetDesc().height
				};
			}
			else if (const auto* pval = std::get_if<std::shared_ptr<Renderbuffer>>(&attachment.second); pval && *pval)
			{
				return {
					(*pval)->GetWidth(),
					(*pval)->GetHeight()
				};
			}
		}

		return { {}, {} }; // <-- not an emoji
	}

	template<>
	void Framebuffer::BlitToBackBuffer(uint16_t p_backBufferWidth, uint16_t p_backBufferHeight) const
	{
		ORHI_ASSERT(IsValid(), "Cannot blit an invalid framebuffer");

		auto [width, height] = GetSize(types::EFramebufferAttachment::COLOR);

		glBlitNamedFramebuffer(
			m_context.id, 0,
			0, 0, width, height,
			0, 0, p_backBufferWidth, p_backBufferHeight,
			GL_COLOR_BUFFER_BIT, GL_LINEAR
		);
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
		ORHI_ASSERT(p_width > 0 && p_height > 0, "Invalid read size");

		Bind();
		glReadPixels(
			p_x, p_y,
			p_width,
			p_height,
			details::EnumToValue<GLenum>(p_format),
			details::EnumToValue<GLenum>(p_type),
			p_data
		);
		Unbind();
	}

	template<>
	const std::string& Framebuffer::GetDebugName() const
	{
		return m_context.debugName;
	}
}

#endif // #if defined(ORHI_COMPILE_OPENGL)
