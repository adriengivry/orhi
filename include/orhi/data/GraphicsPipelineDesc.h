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

namespace orhi::data
{
	/**
	* 
	*/
	template<types::EGraphicsBackend Backend, class DeviceContext, class ShaderModuleContext, class RenderPassContext, class DescriptorSetLayoutContext>
	struct GraphicsPipelineDesc
	{
		std::unordered_map<types::EShaderStageFlags, std::reference_wrapper<api::TShaderModule<Backend, ShaderModuleContext, DeviceContext>>> stages;
		api::TRenderPass<Backend, RenderPassContext, DeviceContext>& renderPass;
		std::span<const VertexAttributeDesc> vertexAttributes;
		std::span<const VertexBindingDesc> vertexBindings;
		std::span<const std::reference_wrapper<api::TDescriptorSetLayout<Backend, DescriptorSetLayoutContext, DeviceContext>>> descriptorSetLayouts;
	};
}
