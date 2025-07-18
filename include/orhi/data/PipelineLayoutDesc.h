/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/PushConstantRange.h>

#include <cstdint>
#include <span>
#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptorSetLayout;
}

namespace orhi::data
{
	/**
	* @brief Pipeline layout descriptor for pipeline layout creation
	* 
	* Defines the complete resource interface for a pipeline layout,
	* including descriptor set layouts and push constant ranges. Pipeline layouts
	* are used to create compatible pipelines and command buffer operations.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct PipelineLayoutDesc
	{
		std::span<const std::reference_wrapper<api::TDescriptorSetLayout<BackendTraits>>> descriptorSetLayouts;
		std::vector<PushConstantRange> pushConstantRanges;
	};
}
