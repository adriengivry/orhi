/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/FramebufferDesc.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext, class RenderPassContext>
	class TFramebuffer final
	{
	public:
		using Desc = data::FramebufferDesc<
			Backend,
			DeviceContext,
			RenderPassContext
		>;

		/**
		* Creates a framebuffer
		*/
		TFramebuffer(
			TDevice<Backend, DeviceContext>& p_device,
			const Desc& p_desc
		);

		/**
		* Destroys the framebuffer
		*/
		~TFramebuffer();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
