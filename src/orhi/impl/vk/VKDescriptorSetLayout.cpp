/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/DescriptorSetLayout.h>
#include <orhi/impl/vk/details/Types.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	DescriptorSetLayout::TDescriptorSetLayout(
		Device& p_device,
		std::initializer_list<data::DescriptorBinding> p_bindings
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE
	}
	{
		std::vector<VkDescriptorSetLayoutBinding> bindings;
		bindings.reserve(p_bindings.size());

		for (const auto& binding : p_bindings)
		{
			bindings.push_back(VkDescriptorSetLayoutBinding{
				.binding = binding.binding,
				.descriptorType = utils::EnumToValue<VkDescriptorType>(binding.type),
				.descriptorCount = 1,
				.stageFlags = utils::EnumToValue<VkShaderStageFlags>(binding.stageFlags),
				.pImmutableSamplers = nullptr // Optional
			});
		}

		VkDescriptorSetLayoutCreateInfo layoutInfo{
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
			.bindingCount = static_cast<uint32_t>(bindings.size()),
			.pBindings = bindings.data()
		};

		VkResult result = vkCreateDescriptorSetLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&layoutInfo,
			nullptr,
			&m_context.handle
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create descriptor set layout!");
	}

	template<>
	DescriptorSetLayout::~TDescriptorSetLayout()
	{
		vkDestroyDescriptorSetLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	data::NativeHandle DescriptorSetLayout::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

template class orhi::api::TDescriptorSetLayout<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
