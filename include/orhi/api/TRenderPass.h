/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/types/EFormat.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TRenderPass final
	{
	public:
		/**
		* Creates a render pass using the give format
		* @param p_device
		* @param p_format
		*/
		TRenderPass(
			TDevice<BackendTraits>& p_device,
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
		BackendTraits::RenderPassContext m_context;
	};
}
