/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Framebuffer.h>

#include <orhi/debug/Assert.h>
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
			.device = p_device,
			.handle = VK_NULL_HANDLE
		}
	{
		auto t = p_desc.attachments.data();

		VkFramebufferCreateInfo framebufferInfo{
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.renderPass = p_desc.renderPass.GetNativeHandle().As<VkRenderPass>(),
			.attachmentCount = 1,
			.pAttachments = reinterpret_cast<const VkImageView*>(p_desc.attachments.data()), // data::NativeHandle same layout as VkImageView
			.width = p_desc.extent.first,
			.height = p_desc.extent.second,
			.layers = 1
		};

		VkResult result = vkCreateFramebuffer(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&framebufferInfo,
			nullptr,
			&m_context.handle
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create framebuffer!");
	}

	template<>
	Framebuffer::~TFramebuffer()
	{
		vkDestroyFramebuffer(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	data::NativeHandle Framebuffer::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

template class orhi::api::TFramebuffer<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
