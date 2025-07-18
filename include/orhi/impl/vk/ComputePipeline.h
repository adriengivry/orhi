/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TComputePipeline.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

struct VkPipeline_T;
typedef VkPipeline_T* VkPipeline;

struct VkPipelineLayout_T;
typedef VkPipelineLayout_T* VkPipelineLayout;

namespace orhi::impl::vk
{
	struct ComputePipelineContext
	{
		Device& device;
		VkPipelineLayout layout;
	};

	using ComputePipeline = api::TComputePipeline<BackendTraits>;
}
