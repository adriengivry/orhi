/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TGraphicsPipeline.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/ContextRegistry.h>

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

	using GraphicsPipeline = api::TGraphicsPipeline<ContextRegistry>;
}
