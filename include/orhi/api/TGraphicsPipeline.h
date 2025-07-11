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
	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	class TGraphicsPipeline final
	{
	public:
		/**
		* Creates a graphics pipeline
		*/
		TGraphicsPipeline(
			TDevice<Backend, CTX_SIG_FWD>& p_device,
			const data::GraphicsPipelineDesc<Backend, CTX_SIG_FWD>& p_desc
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
