/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>

#include <cstdint>
#include <span>
#include <unordered_map>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptorSetLayout;
	template<typename BackendTraits> class TPipelineLayout;
	template<typename BackendTraits> class TShaderModule;
}

namespace orhi::data
{
	/**
	* @brief Compute pipeline descriptor for pipeline creation
	*
	* Defines the complete configuration for creating a compute pipeline,
	* Compute pipelines are immutable once created.
	*
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct ComputePipelineDesc
	{
		api::TShaderModule<BackendTraits>& shader;
		api::TPipelineLayout<BackendTraits>& pipelineLayout;
	};
}
