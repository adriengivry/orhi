/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EShaderStageFlags.h>
#include <orhi/data/ColorBlendStateDesc.h>
#include <orhi/data/DepthStencilStateDesc.h>
#include <orhi/data/DynamicStateDesc.h>
#include <orhi/data/InputAssemblyStateDesc.h>
#include <orhi/data/MultisampleStateDesc.h>
#include <orhi/data/RasterizationStateDesc.h>
#include <orhi/data/TessellationStateDesc.h>
#include <orhi/data/VertexAttributeDesc.h>
#include <orhi/data/VertexBindingDesc.h>
#include <orhi/data/VertexInputStateDesc.h>
#include <orhi/data/ViewportStateDesc.h>

#include <cstdint>
#include <span>
#include <unordered_map>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptorSetLayout;
	template<typename BackendTraits> class TPipelineLayout;
	template<typename BackendTraits> class TRenderPass;
	template<typename BackendTraits> class TShaderModule;
}

namespace orhi::data
{
	/**
	* @brief Graphics pipeline descriptor for pipeline creation
	* 
	* Defines the complete configuration for creating a graphics pipeline,
	* including all shader stages, fixed-function state, descriptor set layouts,
	* and the target render pass. Graphics pipelines are immutable once created.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct GraphicsPipelineDesc
	{
		std::unordered_map<types::EShaderStageFlags, std::reference_wrapper<api::TShaderModule<BackendTraits>>> stages;
		api::TRenderPass<BackendTraits>& renderPass;
		api::TPipelineLayout<BackendTraits>& pipelineLayout;
		
		// State descriptors
		VertexInputStateDesc vertexInputState{};
		InputAssemblyStateDesc inputAssemblyState{};
		TessellationStateDesc tessellationState{};
		ViewportStateDesc viewportState{};
		RasterizationStateDesc rasterizationState{};
		MultisampleStateDesc multisampleState{};
		DepthStencilStateDesc depthStencilState{};
		ColorBlendStateDesc colorBlendState{};
		DynamicStateDesc dynamicState{};
	};
}
