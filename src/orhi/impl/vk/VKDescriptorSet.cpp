/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/DescriptorSet.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/details/Types.h>
#include <orhi/impl/vk/Buffer.h>
#include <orhi/impl/vk/Descriptor.h>
#include <orhi/utils/EnumMapper.h>

#include <vulkan/vulkan.h>

#include <variant>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	DescriptorSet::TDescriptorSet(
		Device& p_device,
		data::NativeHandle p_handle
	) : m_context{
		.device = p_device
	}
	{

	}


	template<>
	DescriptorSet::~TDescriptorSet()
	{

	}

	template<>
	void DescriptorSet::Write(
		const std::unordered_map<uint32_t, data::DescriptorWriteDesc<BackendTraits>>& p_writeDescs
	)
	{
		std::vector<VkWriteDescriptorSet> descriptorWrites;
		std::vector<VkDescriptorBufferInfo> bufferInfos;
		std::vector<VkDescriptorImageInfo> imageInfos;
		
		descriptorWrites.reserve(p_writeDescs.size());
		bufferInfos.reserve(p_writeDescs.size()); // Pessimistic allocation
		imageInfos.reserve(p_writeDescs.size()); // Pessimistic allocation

		for (const auto& [binding, writeDesc] : p_writeDescs)
		{
			std::visit([&](const auto& desc) {
				using T = std::decay_t<decltype(desc)>;
				
				if constexpr (std::is_same_v<T, data::BufferDescriptorWriteInfo<BackendTraits>>)
				{
					// Handle buffer descriptor
					VkDescriptorBufferInfo bufferInfo{
						.buffer = desc.bufferDescriptor.GetNativeHandle().As<VkBuffer>(),
						.offset = 0,
						.range = VK_WHOLE_SIZE
					};
					bufferInfos.push_back(bufferInfo);

					VkWriteDescriptorSet descriptorWrite{
						.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
						.dstSet = m_handle.As<VkDescriptorSet>(),
						.dstBinding = binding,
						.dstArrayElement = 0,
						.descriptorCount = 1,
						.descriptorType = utils::EnumToValue<VkDescriptorType>(desc.descriptorType),
						.pImageInfo = nullptr,
						.pBufferInfo = &bufferInfos.back(),
						.pTexelBufferView = nullptr
					};
					descriptorWrites.push_back(descriptorWrite);
				}
				else if constexpr (std::is_same_v<T, data::TextureSamplerDescriptorWriteInfo<BackendTraits>>)
				{
					// Handle texture/sampler descriptor
					VkDescriptorImageInfo imageInfo{
						.sampler = desc.samplerDescriptor.GetNativeHandle().As<VkSampler>(),
						.imageView = desc.textureDescriptor.GetNativeHandle().As<VkImageView>(),
						.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL // Default layout, could be made configurable
					};
					imageInfos.push_back(imageInfo);

					VkWriteDescriptorSet descriptorWrite{
						.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
						.dstSet = m_handle.As<VkDescriptorSet>(),
						.dstBinding = binding,
						.dstArrayElement = 0,
						.descriptorCount = 1,
						.descriptorType = utils::EnumToValue<VkDescriptorType>(desc.descriptorType),
						.pImageInfo = &imageInfos.back(),
						.pBufferInfo = nullptr,
						.pTexelBufferView = nullptr
					};
					descriptorWrites.push_back(descriptorWrite);
				}
			}, writeDesc);
		}

		if (!descriptorWrites.empty())
		{
			vkUpdateDescriptorSets(
				m_context.device.GetNativeHandle().As<VkDevice>(),
				static_cast<uint32_t>(descriptorWrites.size()),
				descriptorWrites.data(),
				0,
				nullptr
			);
		}
	}
}

template class orhi::api::TDescriptorSet<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
