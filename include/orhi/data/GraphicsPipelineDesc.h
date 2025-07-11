/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <unordered_map>
#include <cstdint>
#include <span>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EShaderStageFlags.h>
#include <orhi/api/TRenderPass.h>
#include <orhi/api/TShaderModule.h>
#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/data/VertexBindingDesc.h>
#include <orhi/data/VertexAttributeDesc.h>
#include <orhi/data/VertexInputStateDesc.h>
#include <orhi/data/InputAssemblyStateDesc.h>
#include <orhi/data/TessellationStateDesc.h>
#include <orhi/data/ViewportStateDesc.h>
#include <orhi/data/RasterizationStateDesc.h>
#include <orhi/data/MultisampleStateDesc.h>
#include <orhi/data/DepthStencilStateDesc.h>
#include <orhi/data/ColorBlendStateDesc.h>
#include <orhi/data/DynamicStateDesc.h>

namespace orhi::data
{
	/**
	* Graphics pipeline descriptor
	*/
	template<typename ContextRegistry>
	struct GraphicsPipelineDesc
	{
		std::unordered_map<types::EShaderStageFlags, std::reference_wrapper<api::TShaderModule<ContextRegistry>>> stages;
		api::TRenderPass<ContextRegistry>& renderPass;
		std::span<const std::reference_wrapper<api::TDescriptorSetLayout<ContextRegistry>>> descriptorSetLayouts;
		
		// Pipeline state descriptors
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
