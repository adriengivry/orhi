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
		// Collect shader stages
		const auto stages = FormatStages(p_desc.stages);
		const auto vertexAttributes = FormatVertexAttributes(p_desc.vertexAttributes);
		const auto vertexBindings = FormatVertexBindings(p_desc.vertexBindings);
		const auto descriptorSetLayouts = FormatDescriptorSetLayouts(p_desc.descriptorSetLayouts);
		
		const auto dynamicStates = std::to_array({
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		});

		// While most of the pipeline state needs to be baked into the pipeline state, a limited amount of the state can actually be
		// changed without recreating the pipeline at draw time. Examples are the size of the viewport, line width and blend constants.
		// If you want to use dynamic state and keep these properties out, then you'll have to fill in a VkPipelineDynamicStateCreateInfo
		// structure like this:
		VkPipelineDynamicStateCreateInfo dynamicState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
			.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size()),
			.pDynamicStates = dynamicStates.data()
		};

		// Describes the format of the vertex data that will be passed to the vertex shader. It describes this in roughly two ways:
		//	Bindings: spacing between data and whether the data is per - vertex or per - instance(see instancing)
		//	Attribute descriptions : type of the attributes passed to the vertex shader, which binding to load them from and at which offset
		VkPipelineVertexInputStateCreateInfo vertexInputState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
			.vertexBindingDescriptionCount = static_cast<uint32_t>(vertexBindings.size()),
			.pVertexBindingDescriptions = vertexBindings.data(), // Optional
			.vertexAttributeDescriptionCount = static_cast<uint32_t>(vertexAttributes.size()),
			.pVertexAttributeDescriptions = vertexAttributes.data() // Optional
		};

		// The VkPipelineInputAssemblyStateCreateInfo struct describes two things:
		// - what kind of geometry will be drawn from the vertices
		// - if primitive restart should be enabled.
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
			.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
			.primitiveRestartEnable = VK_FALSE
		};

		VkPipelineViewportStateCreateInfo viewportState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
			.viewportCount = 1,
			.pViewports = VK_NULL_HANDLE, // Dynamic viewport (VK_DYNAMIC_STATE_VIEWPORT)
			.scissorCount = 1,
			.pScissors = VK_NULL_HANDLE // Dynamic scissor (VK_DYNAMIC_STATE_SCISSOR)
		};

		VkPipelineRasterizationStateCreateInfo rasterizationState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
			.depthClampEnable = VK_FALSE,
			.rasterizerDiscardEnable = VK_FALSE,
			.polygonMode = VK_POLYGON_MODE_FILL,
			.cullMode = VK_CULL_MODE_BACK_BIT,
			.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE,
			.depthBiasEnable = VK_FALSE,
			.depthBiasConstantFactor = 0.0f, // Optional
			.depthBiasClamp = 0.0f, // Optional
			.depthBiasSlopeFactor = 0.0f, // Optional
			.lineWidth = 1.0f
		};

		VkPipelineMultisampleStateCreateInfo multisampleState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
			.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
			.sampleShadingEnable = VK_FALSE,
			.minSampleShading = 1.0f, // Optional
			.pSampleMask = nullptr, // Optional
			.alphaToCoverageEnable = VK_FALSE, // Optional
			.alphaToOneEnable = VK_FALSE // Optional
		};

		// If you are using a depth and/or stencil buffer, then you also need to configure the depth and stencil tests using
		// VkPipelineDepthStencilStateCreateInfo. We don't have one right now, so we can simply pass a nullptr instead of a
		// pointer to such a struct. We'll get back to it in the depth buffering chapter.

		VkPipelineColorBlendAttachmentState colorBlendAttachmentState{
			.blendEnable = VK_FALSE,
			.srcColorBlendFactor = VK_BLEND_FACTOR_ONE, // Optional
			.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO, // Optional
			.colorBlendOp = VK_BLEND_OP_ADD, // Optional
			.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE, // Optional
			.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO, // Optional
			.alphaBlendOp = VK_BLEND_OP_ADD, // Optional
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
		};

		VkPipelineColorBlendStateCreateInfo colorBlendState{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
			.logicOpEnable = VK_FALSE,
			.logicOp = VK_LOGIC_OP_COPY, // Optional
			.attachmentCount = 1,
			.pAttachments = &colorBlendAttachmentState,
			.blendConstants = {
				0.0f, // Optional
				0.0f, // Optional
				0.0f, // Optional
				0.0f // Optional
			}
		};

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = static_cast<uint32_t>(descriptorSetLayouts.size()),
			.pSetLayouts = descriptorSetLayouts.data(),
			.pushConstantRangeCount = 0, // Optional
			.pPushConstantRanges = nullptr // Optional
		};

		VkResult pipelineLayoutCreationResult = vkCreatePipelineLayout(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&pipelineLayoutInfo,
			nullptr,
			&m_context.layout
		);
		
		ORHI_ASSERT(pipelineLayoutCreationResult == VK_SUCCESS, "failed to create pipeline layout!");

		VkGraphicsPipelineCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
			.stageCount = static_cast<uint32_t>(stages.size()),
			.pStages = stages.data(),
			.pVertexInputState = &vertexInputState,
			.pInputAssemblyState = &inputAssemblyState,
			.pViewportState = &viewportState,
			.pRasterizationState = &rasterizationState,
			.pMultisampleState = &multisampleState,
			.pColorBlendState = &colorBlendState,
			.pDynamicState = &dynamicState,
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
