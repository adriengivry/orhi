/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Framebuffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/impl/vk/Descriptor.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace
{
	orhi::types::ETextureAspectFlags GetAttachmentAspectFlags(
		const orhi::data::FramebufferAttachmentDesc<orhi::impl::vk::BackendTraits>& p_attachment
	)
	{
		if (p_attachment.aspectFlags != orhi::types::ETextureAspectFlags::NONE)
		{
			return p_attachment.aspectFlags;
		}

		if (p_attachment.type != orhi::types::EAttachmentType::DEPTH_STENCIL)
		{
			return orhi::types::ETextureAspectFlags::COLOR;
		}

		switch (p_attachment.format)
		{
		case orhi::types::EFormat::S8_UINT:
			return orhi::types::ETextureAspectFlags::STENCIL;
		case orhi::types::EFormat::D16_UNORM_S8_UINT:
		case orhi::types::EFormat::D24_UNORM_S8_UINT:
		case orhi::types::EFormat::D32_SFLOAT_S8_UINT:
			return orhi::types::ETextureAspectFlags::DEPTH | orhi::types::ETextureAspectFlags::STENCIL;
		default:
			return orhi::types::ETextureAspectFlags::DEPTH;
		}
	}
}

namespace orhi
{
	template<>
	Framebuffer::TFramebuffer(
		Device& p_device,
		const data::FramebufferDesc<BackendTraits>& p_desc
	) :
		m_context{
			.device = p_device,
			.extent = p_desc.extent
		}
	{
		ORHI_ASSERT(p_desc.attachments.size() > 0, "Framebuffer requires at least one attachment");
		ORHI_ASSERT(p_desc.extent.width > 0 && p_desc.extent.height > 0, "Framebuffer extent must be non-zero");

		m_context.attachments.reserve(p_desc.attachments.size());

		for (const auto& attachment : p_desc.attachments)
		{
			const auto image = attachment.descriptor.get().GetResourceNativeHandle();
			const auto imageView = attachment.descriptor.get().GetNativeHandle();
			ORHI_ASSERT(image.As<VkImage>() != VK_NULL_HANDLE, "Framebuffer attachment must reference an image");
			ORHI_ASSERT(imageView.As<VkImageView>() != VK_NULL_HANDLE, "Framebuffer attachment must have an image view");

			m_context.attachments.push_back(FramebufferAttachment{
				.image = image,
				.imageView = imageView,
				.type = attachment.type,
				.format = attachment.format,
				.initialLayout = attachment.initialLayout,
				.finalLayout = attachment.finalLayout,
				.aspectFlags = GetAttachmentAspectFlags(attachment)
			});
		}

		m_handle = impl::common::NativeHandle{ &m_context };
	}

	template<>
	Framebuffer::~TFramebuffer()
	{
	}
}

template class orhi::api::TFramebuffer<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
