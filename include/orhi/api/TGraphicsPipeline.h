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
	template<typename BackendTraits>
	class TGraphicsPipeline final
	{
	public:
		/**
		* Creates a graphics pipeline
		*/
		TGraphicsPipeline(
			TDevice<BackendTraits>& p_device,
			const data::GraphicsPipelineDesc<BackendTraits>& p_desc
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
		BackendTraits::GraphicsPipelineContext m_context;
	};
}
