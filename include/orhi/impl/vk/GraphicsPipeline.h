/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TGraphicsPipeline.h>
#include <orhi/impl/vk/Device.h>

struct VkPipeline_T;
typedef VkPipeline_T* VkPipeline;

struct VkPipelineLayout_T;
typedef VkPipelineLayout_T* VkPipelineLayout;

namespace orhi::impl::vk
{
	struct GraphicsPipelineContext 
	{
		Device& device;
		VkPipelineLayout layout;
		VkPipeline handle;
	};

	using GraphicsPipeline = api::TGraphicsPipeline<
		types::EGraphicsBackend::VULKAN,
		struct GraphicsPipelineContext,
		struct DeviceContext,
		struct ShaderModuleContext,
		struct RenderPassContext,
		struct DescriptorSetLayoutContext
	>;
}
