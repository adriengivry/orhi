/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EFormat.h>
#include <orhi/api/TDevice.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TRenderPass final
	{
	public:
		/**
		* Creates a render pass using the give format
		* @param p_device
		* @param p_format
		*/
		TRenderPass(
			TDevice<Backend, ContextRegistry>& p_device,
			types::EFormat p_format
		);

		/**
		* Destroys the render pass
		*/
		~TRenderPass();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		ContextRegistry::RenderPassContext m_context;
	};
}
