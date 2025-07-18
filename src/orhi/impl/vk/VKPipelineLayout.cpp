/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/PipelineLayout.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/detail/Types.h>
#include <orhi/impl/vk/DescriptorSetLayout.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace
{
	auto FormatDescriptorSetLayouts(std::span<const std::reference_wrapper<orhi::impl::vk::DescriptorSetLayout>> p_descriptorSetLayouts)
	{
		std::vector<VkDescriptorSetLayout> formattedDescriptorSetLayouts;
		formattedDescriptorSetLayouts.reserve(p_descriptorSetLayouts.size());

		for (auto& descriptorSetLayout : p_descriptorSetLayouts)
		{
			formattedDescriptorSetLayouts.push_back(
				descriptorSetLayout
					.get()
					.GetNativeHandle()
					.As<VkDescriptorSetLayout>()
			);
		}

		return formattedDescriptorSetLayouts;
	}

	auto FormatPushConstantRanges(const std::vector<orhi::data::PushConstantRange>& p_pushConstantRanges)
	{
		std::vector<VkPushConstantRange> formattedPushConstantRanges;
		formattedPushConstantRanges.reserve(p_pushConstantRanges.size());

		for (const auto& pushConstantRange : p_pushConstantRanges)
		{
			formattedPushConstantRanges.push_back(VkPushConstantRange{
				.stageFlags = orhi::utils::EnumToValue<VkShaderStageFlags>(pushConstantRange.stageFlags),
				.offset = pushConstantRange.offset,
				.size = pushConstantRange.size
			});
		}

		return formattedPushConstantRanges;
	}
}

namespace orhi
{
	template<>
	PipelineLayout::TPipelineLayout(
		Device& p_device,
		const data::PipelineLayoutDesc<BackendTraits>& p_desc
	) : m_context{
		.device = p_device
	}
	{
		// Collect and format pipeline layout components
		const auto descriptorSetLayouts = FormatDescriptorSetLayouts(p_desc.descriptorSetLayouts);
		const auto pushConstantRanges = FormatPushConstantRanges(p_desc.pushConstantRanges);

		// Create pipeline layout
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size()),
			.pSetLayouts = descriptorSetLayouts.data(),
			.pushConstantRangeCount = static_cast<uint32_t>(pushConstantRanges.size()),
			.pPushConstantRanges = pushConstantRanges.data()
		};

		VkResult pipelineLayoutCreationResult = vkCreatePipelineLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&pipelineLayoutInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkPipelineLayout&>()
		);

		ORHI_ASSERT(pipelineLayoutCreationResult == VK_SUCCESS, "failed to create pipeline layout!");
	}

	template<>
	PipelineLayout::~TPipelineLayout()
	{
		vkDestroyPipelineLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkPipelineLayout>(),
			nullptr
		);
	}
}

template class orhi::api::TPipelineLayout<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
