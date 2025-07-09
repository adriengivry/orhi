/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Descriptor.h>
#include <orhi/impl/vk/Texture.h>
#include <orhi/impl/vk/details/Types.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Descriptor::TDescriptor(
		Device& p_device,
		const TextureViewDesc& p_desc
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE,
		.type = EVulkanDescriptorType::IMAGE_VIEW
	}
	{
		VkImageViewCreateInfo viewInfo{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = p_desc.texture.GetNativeHandle().As<VkImage>(),
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = utils::EnumToValue<VkFormat>(p_desc.format),
			.subresourceRange = {
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = p_desc.mipLevels,
				.baseArrayLayer = 0,
				.layerCount = p_desc.arrayLayers,
			}
		};

		VkResult result = vkCreateImageView(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&viewInfo,
			nullptr,
			&reinterpret_cast<VkImageView&>(m_context.handle)
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create texture image view!");
	}

	template<>
	Descriptor::~TDescriptor()
	{
		switch (m_context.type)
		{
		case EVulkanDescriptorType::IMAGE_VIEW:
			vkDestroyImageView(
				m_context.device.GetNativeHandle().As<VkDevice>(),
				m_context.handle.As<VkImageView>(),
				nullptr
			);
			break;
		}
	}

	template<>
	data::NativeHandle Descriptor::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
