/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/DescriptorSet.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	DescriptorSet::TDescriptorSet(
		Device& p_device,
		data::NativeHandle p_handle
	) : m_context{
		.device = p_device,
		.handle = p_handle.As<VkDescriptorSet>()
	}
	{

	}


	template<>
	DescriptorSet::~TDescriptorSet()
	{

	}

	template<>
	void DescriptorSet::Write(
		types::EDescriptorType p_type,
		std::span<const std::reference_wrapper<Buffer>> p_buffers
	)
	{
		std::vector<VkDescriptorBufferInfo> bufferInfos;
		bufferInfos.reserve(p_buffers.size());

		for (auto& buffer : p_buffers)
		{
			VkDescriptorBufferInfo bufferInfo{
				.buffer = buffer.get().GetNativeHandle().As<VkBuffer>(),
				.offset = 0,
				.range = VK_WHOLE_SIZE
			};

			bufferInfos.push_back(bufferInfo);
		}

		VkWriteDescriptorSet descriptorWrite{
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.dstSet = m_context.handle,
			.dstBinding = 0,
			.dstArrayElement = 0,
			.descriptorCount = 1,
			.descriptorType = static_cast<VkDescriptorType>(p_type),
			.pImageInfo = nullptr, // Optional
			.pBufferInfo = bufferInfos.data(),
			.pTexelBufferView = nullptr, // Optional
		};

		vkUpdateDescriptorSets(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			1,
			&descriptorWrite,
			0,
			nullptr
		);
	}

	template<>
	data::NativeHandle DescriptorSet::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
