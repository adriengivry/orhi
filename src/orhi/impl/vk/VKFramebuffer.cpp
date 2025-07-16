/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Framebuffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/impl/vk/Descriptor.h>
#include <orhi/impl/vk/RenderPass.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Framebuffer::TFramebuffer(
		Device& p_device,
		const data::FramebufferDesc<BackendTraits>& p_desc
	) :
		m_context{
			.device = p_device
		}
	{
		std::vector<VkImageView> imageViews;
		imageViews.reserve(p_desc.attachments.size());

		for (const auto& attachment : p_desc.attachments)
		{
			imageViews.push_back(attachment.get().GetNativeHandle().As<VkImageView>());
		}

		VkFramebufferCreateInfo framebufferInfo{
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.renderPass = p_desc.renderPass.GetNativeHandle().As<VkRenderPass>(),
			.attachmentCount = static_cast<uint32_t>(imageViews.size()),
			.pAttachments = imageViews.data(),
			.width = p_desc.extent.width,
			.height = p_desc.extent.height,
			.layers = 1
		};

		VkResult result = vkCreateFramebuffer(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&framebufferInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkFramebuffer&>()
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create framebuffer!");
	}

	template<>
	Framebuffer::~TFramebuffer()
	{
		vkDestroyFramebuffer(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkFramebuffer>(),
			nullptr
		);
	}
}

template class orhi::api::TFramebuffer<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
