/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TPipeline.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

struct VkPipeline_T;
typedef VkPipeline_T* VkPipeline;

struct VkPipelineLayout_T;
typedef VkPipelineLayout_T* VkPipelineLayout;

namespace orhi::impl::vk
{
	struct PipelineContext 
	{
		Device& device;
		VkPipelineLayout layout;
	};

	using Pipeline = api::TPipeline<BackendTraits>;
}
