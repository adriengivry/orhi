/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Descriptor.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/Texture.h>
#include <orhi/impl/vk/details/Types.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Descriptor::TDescriptor(
		Device& p_device,
		const data::TextureViewDesc<BackendTraits>& p_desc
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
	Descriptor::TDescriptor(
		Device& p_device,
		const data::SamplerDesc& p_desc
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE,
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
			&reinterpret_cast<VkSampler&>(m_context.handle)
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
				m_context.handle.As<VkImageView>(),
				nullptr
			);
			break;

		case EVulkanDescriptorType::SAMPLER:
			vkDestroySampler(
				m_context.device.GetNativeHandle().As<VkDevice>(),
				m_context.handle.As<VkSampler>(),
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

template class orhi::api::TDescriptor<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
