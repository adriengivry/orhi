/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/GraphicsPipeline.h>
#include <orhi/impl/vk/details/Types.h>
#include <orhi/data/VertexInputStateDesc.h>
#include <orhi/data/InputAssemblyStateDesc.h>
#include <orhi/data/ViewportStateDesc.h>
#include <orhi/data/RasterizationStateDesc.h>
#include <orhi/data/MultisampleStateDesc.h>
#include <orhi/data/DepthStencilStateDesc.h>
#include <orhi/data/ColorBlendStateDesc.h>
#include <orhi/data/DynamicStateDesc.h>
#include <vulkan/vulkan.h>
#include <array>

using namespace orhi::impl::vk;

namespace
{
	auto FormatStages(const std::unordered_map<orhi::types::EShaderStageFlags, std::reference_wrapper<ShaderModule>>& p_stages)
	{
		std::vector<VkPipelineShaderStageCreateInfo> formattedStages;
		formattedStages.reserve(p_stages.size());

		for (auto& [stageType, stageInstance] : p_stages)
		{
			formattedStages.push_back(VkPipelineShaderStageCreateInfo{
				.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
				.stage = static_cast<VkShaderStageFlagBits>(
					orhi::utils::EnumToValue<VkShaderStageFlags>(stageType)
				),
				.module = stageInstance.get().GetNativeHandle().As<VkShaderModule>(),
				.pName = "main"
			});
		}

		return formattedStages;
	}

	auto FormatVertexAttributes(const std::span<const orhi::data::VertexAttributeDesc>& p_attributes)
	{
		std::vector<VkVertexInputAttributeDescription> formattedAttributes;
		formattedAttributes.reserve(p_attributes.size());

		for (auto& attribute : p_attributes)
		{
			formattedAttributes.push_back(VkVertexInputAttributeDescription{
				.location = attribute.location,
				.binding = attribute.binding,
				.format = orhi::utils::EnumToValue<VkFormat>(attribute.format),
				.offset = attribute.offset,
			});
		}

		return formattedAttributes;
	}

	auto FormatVertexBindings(std::span<const orhi::data::VertexBindingDesc> p_bindings)
	{
		std::vector<VkVertexInputBindingDescription> formattedBindings;
		formattedBindings.reserve(p_bindings.size());

		for (auto& binding : p_bindings)
		{
			formattedBindings.push_back(VkVertexInputBindingDescription{
				.binding = binding.binding,
				.stride = binding.stride,
				.inputRate = VK_VERTEX_INPUT_RATE_VERTEX
			});
		}

		return formattedBindings;
	}

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

	auto FormatInputAssemblyState(const orhi::data::InputAssemblyStateDesc& p_desc)
	{
		return VkPipelineInputAssemblyStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			.topology = orhi::utils::EnumToValue<VkPrimitiveTopology>(p_desc.topology),
			.primitiveRestartEnable = p_desc.primitiveRestartEnable ? VK_TRUE : VK_FALSE
		};
	}

	auto FormatRasterizationState(const orhi::data::RasterizationStateDesc& p_desc)
	{
		return VkPipelineRasterizationStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
			.depthClampEnable = p_desc.depthClampEnable ? VK_TRUE : VK_FALSE,
			.rasterizerDiscardEnable = p_desc.rasterizerDiscardEnable ? VK_TRUE : VK_FALSE,
			.polygonMode = orhi::utils::EnumToValue<VkPolygonMode>(p_desc.polygonMode),
			.cullMode = orhi::utils::EnumToValue<VkCullModeFlags>(p_desc.cullMode),
			.frontFace = orhi::utils::EnumToValue<VkFrontFace>(p_desc.frontFace),
			.depthBiasEnable = p_desc.depthBiasEnable ? VK_TRUE : VK_FALSE,
			.depthBiasConstantFactor = p_desc.depthBiasConstantFactor,
			.depthBiasClamp = p_desc.depthBiasClamp,
			.depthBiasSlopeFactor = p_desc.depthBiasSlopeFactor,
			.lineWidth = p_desc.lineWidth
		};
	}

	auto FormatMultisampleState(const orhi::data::MultisampleStateDesc& p_desc)
	{
		return VkPipelineMultisampleStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			.rasterizationSamples = orhi::utils::EnumToValue<VkSampleCountFlagBits>(p_desc.rasterizationSamples),
			.sampleShadingEnable = p_desc.sampleShadingEnable ? VK_TRUE : VK_FALSE,
			.minSampleShading = p_desc.minSampleShading,
			.pSampleMask = p_desc.pSampleMask,
			.alphaToCoverageEnable = p_desc.alphaToCoverageEnable ? VK_TRUE : VK_FALSE,
			.alphaToOneEnable = p_desc.alphaToOneEnable ? VK_TRUE : VK_FALSE
		};
	}

	auto FormatStencilOpState(const orhi::data::StencilOpStateDesc& p_desc)
	{
		return VkStencilOpState{
			.failOp = orhi::utils::EnumToValue<VkStencilOp>(p_desc.failOp),
			.passOp = orhi::utils::EnumToValue<VkStencilOp>(p_desc.passOp),
			.depthFailOp = orhi::utils::EnumToValue<VkStencilOp>(p_desc.depthFailOp),
			.compareOp = orhi::utils::EnumToValue<VkCompareOp>(p_desc.compareOp),
			.compareMask = p_desc.compareMask,
			.writeMask = p_desc.writeMask,
			.reference = p_desc.reference
		};
	}

	auto FormatDepthStencilState(const orhi::data::DepthStencilStateDesc& p_desc)
	{
		return VkPipelineDepthStencilStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
			.depthTestEnable = p_desc.depthTestEnable ? VK_TRUE : VK_FALSE,
			.depthWriteEnable = p_desc.depthWriteEnable ? VK_TRUE : VK_FALSE,
			.depthCompareOp = orhi::utils::EnumToValue<VkCompareOp>(p_desc.depthCompareOp),
			.depthBoundsTestEnable = p_desc.depthBoundsTestEnable ? VK_TRUE : VK_FALSE,
			.stencilTestEnable = p_desc.stencilTestEnable ? VK_TRUE : VK_FALSE,
			.front = FormatStencilOpState(p_desc.front),
			.back = FormatStencilOpState(p_desc.back),
			.minDepthBounds = p_desc.minDepthBounds,
			.maxDepthBounds = p_desc.maxDepthBounds
		};
	}

	auto FormatColorBlendAttachments(const std::span<const orhi::data::ColorBlendAttachmentStateDesc>& p_attachments)
	{
		std::vector<VkPipelineColorBlendAttachmentState> formattedAttachments;
		formattedAttachments.reserve(p_attachments.size());

		for (auto& attachment : p_attachments)
		{
			formattedAttachments.push_back(VkPipelineColorBlendAttachmentState{
				.blendEnable = attachment.blendEnable ? VK_TRUE : VK_FALSE,
				.srcColorBlendFactor = orhi::utils::EnumToValue<VkBlendFactor>(attachment.srcColorBlendFactor),
				.dstColorBlendFactor = orhi::utils::EnumToValue<VkBlendFactor>(attachment.dstColorBlendFactor),
				.colorBlendOp = orhi::utils::EnumToValue<VkBlendOp>(attachment.colorBlendOp),
				.srcAlphaBlendFactor = orhi::utils::EnumToValue<VkBlendFactor>(attachment.srcAlphaBlendFactor),
				.dstAlphaBlendFactor = orhi::utils::EnumToValue<VkBlendFactor>(attachment.dstAlphaBlendFactor),
				.alphaBlendOp = orhi::utils::EnumToValue<VkBlendOp>(attachment.alphaBlendOp),
				.colorWriteMask = orhi::utils::EnumToValue<VkColorComponentFlags>(attachment.colorWriteMask)
			});
		}

		return formattedAttachments;
	}

	auto FormatColorBlendState(const orhi::data::ColorBlendStateDesc& p_desc, const std::vector<VkPipelineColorBlendAttachmentState>& p_attachments)
	{
		return VkPipelineColorBlendStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
			.logicOpEnable = p_desc.logicOpEnable ? VK_TRUE : VK_FALSE,
			.logicOp = orhi::utils::EnumToValue<VkLogicOp>(p_desc.logicOp),
			.attachmentCount = static_cast<uint32_t>(p_attachments.size()),
			.pAttachments = p_attachments.data(),
			.blendConstants = {
				p_desc.blendConstants[0],
				p_desc.blendConstants[1],
				p_desc.blendConstants[2],
				p_desc.blendConstants[3]
			}
		};
	}

	auto FormatDynamicStates(const std::span<const orhi::types::EDynamicState>& p_dynamicStates)
	{
		std::vector<VkDynamicState> formattedDynamicStates;
		formattedDynamicStates.reserve(p_dynamicStates.size());

		for (auto& dynamicState : p_dynamicStates)
		{
			formattedDynamicStates.push_back(orhi::utils::EnumToValue<VkDynamicState>(dynamicState));
		}

		return formattedDynamicStates;
	}

	auto FormatDynamicState(const orhi::data::DynamicStateDesc& p_desc, const std::vector<VkDynamicState>& p_dynamicStates)
	{
		return VkPipelineDynamicStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
			.dynamicStateCount = static_cast<uint32_t>(p_dynamicStates.size()),
			.pDynamicStates = p_dynamicStates.data()
		};
	}

	auto FormatVertexInputState(const orhi::data::VertexInputStateDesc& p_desc, 
		const std::vector<VkVertexInputBindingDescription>& p_bindings,
		const std::vector<VkVertexInputAttributeDescription>& p_attributes)
	{
		return VkPipelineVertexInputStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.vertexBindingDescriptionCount = static_cast<uint32_t>(p_bindings.size()),
			.pVertexBindingDescriptions = p_bindings.data(),
			.vertexAttributeDescriptionCount = static_cast<uint32_t>(p_attributes.size()),
			.pVertexAttributeDescriptions = p_attributes.data()
		};
	}

	auto FormatViewports(const std::span<const orhi::data::ViewportDesc>& p_viewports)
	{
		std::vector<VkViewport> formattedViewports;
		formattedViewports.reserve(p_viewports.size());

		for (auto& viewport : p_viewports)
		{
			formattedViewports.push_back(VkViewport{
				.x = viewport.x,
				.y = viewport.y,
				.width = viewport.width,
				.height = viewport.height,
				.minDepth = viewport.minDepth,
				.maxDepth = viewport.maxDepth
			});
		}

		return formattedViewports;
	}

	auto FormatScissors(const std::span<const orhi::data::Rect2D>& p_scissors)
	{
		std::vector<VkRect2D> formattedScissors;
		formattedScissors.reserve(p_scissors.size());

		for (auto& scissor : p_scissors)
		{
			formattedScissors.push_back(VkRect2D{
				.offset = { scissor.offset.first, scissor.offset.second },
				.extent = { scissor.extent.first, scissor.extent.second }
			});
		}

		return formattedScissors;
	}

	auto FormatViewportState(const orhi::data::ViewportStateDesc& p_desc,
		const std::vector<VkViewport>& p_viewports,
		const std::vector<VkRect2D>& p_scissors)
	{
		return VkPipelineViewportStateCreateInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.viewportCount = static_cast<uint32_t>(p_viewports.size()),
			.pViewports = p_viewports.empty() ? nullptr : p_viewports.data(),
			.scissorCount = static_cast<uint32_t>(p_scissors.size()),
			.pScissors = p_scissors.empty() ? nullptr : p_scissors.data()
		};
	}
}

namespace orhi
{
	template<>
	GraphicsPipeline::TGraphicsPipeline(
		Device& p_device,
		const Desc& p_desc
	) : m_context{
		.device = p_device,
		.layout = VK_NULL_HANDLE,
		.handle = VK_NULL_HANDLE
	}
	{
		// Collect and format pipeline components
		const auto stages = FormatStages(p_desc.stages);
		const auto vertexAttributes = FormatVertexAttributes(p_desc.vertexInputState.vertexAttributes);
		const auto vertexBindings = FormatVertexBindings(p_desc.vertexInputState.vertexBindings);
		const auto descriptorSetLayouts = FormatDescriptorSetLayouts(p_desc.descriptorSetLayouts);
		
		// Format pipeline states using descriptors
		const auto vertexInputState = FormatVertexInputState(p_desc.vertexInputState, vertexBindings, vertexAttributes);
		const auto inputAssemblyState = FormatInputAssemblyState(p_desc.inputAssemblyState);
		
		const auto viewports = FormatViewports(p_desc.viewportState.viewports);
		const auto scissors = FormatScissors(p_desc.viewportState.scissors);
		const auto viewportState = FormatViewportState(p_desc.viewportState, viewports, scissors);
		
		const auto rasterizationState = FormatRasterizationState(p_desc.rasterizationState);
		const auto multisampleState = FormatMultisampleState(p_desc.multisampleState);
		const auto depthStencilState = FormatDepthStencilState(p_desc.depthStencilState);
		
		const auto colorBlendAttachments = FormatColorBlendAttachments(p_desc.colorBlendState.attachments);
		const auto colorBlendState = FormatColorBlendState(p_desc.colorBlendState, colorBlendAttachments);
		
		const auto dynamicStatesArray = FormatDynamicStates(p_desc.dynamicState.dynamicStates);
		const auto dynamicState = FormatDynamicState(p_desc.dynamicState, dynamicStatesArray);

		// Create pipeline layout
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size()),
			.pSetLayouts = descriptorSetLayouts.data(),
			.pushConstantRangeCount = 0,
			.pPushConstantRanges = nullptr
		};

		VkResult pipelineLayoutCreationResult = vkCreatePipelineLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&pipelineLayoutInfo,
			nullptr,
			&m_context.layout
		);
		
		ORHI_ASSERT(pipelineLayoutCreationResult == VK_SUCCESS, "failed to create pipeline layout!");

		// Create graphics pipeline
		VkGraphicsPipelineCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			.stageCount = static_cast<uint32_t>(stages.size()),
			.pStages = stages.data(),
			.pVertexInputState = &vertexInputState,
			.pInputAssemblyState = &inputAssemblyState,
			.pViewportState = &viewportState,
			.pRasterizationState = &rasterizationState,
			.pMultisampleState = &multisampleState,
			.pDepthStencilState = p_desc.depthStencilState.depthTestEnable || p_desc.depthStencilState.stencilTestEnable ? &depthStencilState : nullptr,
			.pColorBlendState = &colorBlendState,
			.pDynamicState = dynamicStatesArray.empty() ? nullptr : &dynamicState,
			.layout = m_context.layout,
			.renderPass = p_desc.renderPass.GetNativeHandle().As<VkRenderPass>(),
		};

		VkResult pipelineCreationResult = vkCreateGraphicsPipelines(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			VK_NULL_HANDLE,
			1,
			&createInfo,
			nullptr,
			&m_context.handle
		);
		
		ORHI_ASSERT(pipelineCreationResult == VK_SUCCESS, "failed to create graphics pipeline!");
	}

	template<>
	GraphicsPipeline::~TGraphicsPipeline()
	{
		vkDestroyPipelineLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.layout,
			nullptr
		);

		vkDestroyPipeline(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	data::NativeHandle GraphicsPipeline::GetLayoutHandle() const
	{
		return m_context.layout;
	}

	template<>
	data::NativeHandle GraphicsPipeline::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
