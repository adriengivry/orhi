/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/DescriptorPool.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace
{
	// TODO: Remove
	constexpr uint32_t MAX_FRAMES_IN_FLIGHT = 2;
}

namespace orhi
{
	template<>
	DescriptorPool::TDescriptorPool(
		Device& p_device
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE
	}
	{
		VkDescriptorPoolSize poolSize{
			.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			.descriptorCount = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT)
		};

		VkDescriptorPoolCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
			.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT),
			.poolSizeCount = 1,
			.pPoolSizes = &poolSize,
		};

		VkResult result = vkCreateDescriptorPool(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_context.handle
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create descriptor pool");
	}

	template<>
	DescriptorPool::~TDescriptorPool()
	{
		vkDestroyDescriptorPool(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	std::vector<std::reference_wrapper<DescriptorSet>> DescriptorPool::AllocateDescriptorSets(
		const DescriptorSetLayout& p_layout,
		uint32_t p_count
	)
	{
		std::vector<VkDescriptorSetLayout> layouts(p_count, p_layout.GetNativeHandle().As<VkDescriptorSetLayout>());

		std::vector<std::reference_wrapper<DescriptorSet>> output;
		output.reserve(p_count);

		VkDescriptorSetAllocateInfo allocInfo{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.descriptorPool = m_context.handle,
			.descriptorSetCount = p_count,
			.pSetLayouts = layouts.data()
		};

		std::vector<VkDescriptorSet> allocatedDescriptorSets(p_count);

		VkResult result = vkAllocateDescriptorSets(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&allocInfo,
			allocatedDescriptorSets.data()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to allocate descriptor sets!");

		for (auto allocatedDescriptorSet : allocatedDescriptorSets)
		{
			output.emplace_back(
				m_context.descriptorSets.emplace_back(DescriptorSet{
					m_context.device,
					allocatedDescriptorSet
				})
			);
		}

		return output;
	}

	template<>
	data::NativeHandle DescriptorPool::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
