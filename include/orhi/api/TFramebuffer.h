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
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TFramebuffer final
	{
	public:
		/**
		* Creates a framebuffer
		*/
		TFramebuffer(
			TDevice<Backend, ContextRegistry>& p_device,
			const data::FramebufferDesc<Backend, ContextRegistry>& p_desc
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
		typename ContextRegistry::FramebufferContext m_context;
	};
}
