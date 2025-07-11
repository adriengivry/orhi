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
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TGraphicsPipeline final
	{
	public:
		/**
		* Creates a graphics pipeline
		*/
		TGraphicsPipeline(
			TDevice<Backend, ContextRegistry>& p_device,
			const data::GraphicsPipelineDesc<Backend, ContextRegistry>& p_desc
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
		ContextRegistry::GraphicsPipelineContext m_context;
	};
}
