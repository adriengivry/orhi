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
	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	class TFramebuffer final
	{
	public:
		/**
		* Creates a framebuffer
		*/
		TFramebuffer(
			TDevice<Backend, CTX_SIG_FWD>& p_device,
			const data::FramebufferDesc<Backend, CTX_SIG_FWD>& p_desc
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
		FramebufferContext m_context;
	};
}
