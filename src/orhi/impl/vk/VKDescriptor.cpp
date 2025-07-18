/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Descriptor.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/detail/Types.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/Texture.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Descriptor::TDescriptor(
		Device& p_device,
		const data::TextureViewDesc& p_desc
	) : m_context{
		.device = p_device,
		.type = EVulkanDescriptorType::IMAGE_VIEW
	}
	{
		VkImageViewCreateInfo viewInfo{
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
			.image = p_desc.texture.As<VkImage>(),
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = utils::EnumToValue<VkFormat>(p_desc.format),
			.subresourceRange = {
				.aspectMask = utils::EnumToValue<VkImageAspectFlags>(p_desc.aspectFlags),
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
			&m_handle.ReinterpretAs<VkImageView&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create texture image view!");
	}

	template<>
	Descriptor::TDescriptor(
		Device& p_device,
		const data::SamplerDesc& p_desc
	) : m_context{
		.device = p_device,
		.type = EVulkanDescriptorType::SAMPLER
	}
	{
		VkSamplerCreateInfo  samplerInfo{
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
			.magFilter = utils::EnumToValue<VkFilter>(p_desc.magFilter),
			.minFilter = utils::EnumToValue<VkFilter>(p_desc.minFilter),
			.mipmapMode = utils::EnumToValue<VkSamplerMipmapMode>(p_desc.mipmapMode),
			.addressModeU = utils::EnumToValue<VkSamplerAddressMode>(p_desc.addressModeU),
			.addressModeV = utils::EnumToValue<VkSamplerAddressMode>(p_desc.addressModeV),
			.addressModeW = utils::EnumToValue<VkSamplerAddressMode>(p_desc.addressModeW),
			.mipLodBias = p_desc.mipLodBias,
			.anisotropyEnable = p_desc.anisotropy,
			.maxAnisotropy = p_desc.anisotropy ? p_device.GetInfo().maxSamplerAnisotropy : 1.0f,
			.compareEnable = p_desc.compareEnable,
			.compareOp = utils::EnumToValue<VkCompareOp>(p_desc.compareOp),
			.minLod = p_desc.minLod,
			.maxLod = p_desc.maxLod,
			.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
			.unnormalizedCoordinates = p_desc.unnormalizedCoordinates,
		};

		VkResult result = vkCreateSampler(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&samplerInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkSampler&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create sampler!");
	}

	template<>
	Descriptor::~TDescriptor()
	{
		switch (m_context.type)
		{
		case EVulkanDescriptorType::IMAGE_VIEW:
			vkDestroyImageView(
				m_context.device.GetNativeHandle().As<VkDevice>(),
				m_handle.As<VkImageView>(),
				nullptr
			);
			break;

		case EVulkanDescriptorType::SAMPLER:
			vkDestroySampler(
				m_context.device.GetNativeHandle().As<VkDevice>(),
				m_handle.As<VkSampler>(),
				nullptr
			);
			break;
		}
	}
}

template class orhi::api::TDescriptor<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
