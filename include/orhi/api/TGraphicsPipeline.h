/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/GraphicsPipelineDesc.h>
#include <orhi/api/TDevice.h>

namespace orhi::api
{
	template<
		types::EGraphicsBackend Backend,
		class GraphicsPipelineContext,
		class DeviceContext,
		class ShaderModuleContext,
		class RenderPassContext,
		class DescriptorSetLayoutContext
	>
	class TGraphicsPipeline final
	{
	public:
		using Desc = data::GraphicsPipelineDesc<
			Backend,
			DeviceContext,
			ShaderModuleContext,
			RenderPassContext,
			DescriptorSetLayoutContext
		>;

		/**
		* Creates a graphics pipeline
		*/
		TGraphicsPipeline(
			TDevice<Backend, DeviceContext>& p_device,
			const Desc& p_desc
		);

		/**
		* Destructor of the graphics pipeline
		*/
		~TGraphicsPipeline();

		/**
		* Returns the graphics pipeline layout native handle
		*/
		data::NativeHandle GetLayoutHandle() const;

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		GraphicsPipelineContext m_context;
	};
}
