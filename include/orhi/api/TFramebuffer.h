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
	template<typename ContextRegistry>
	class TFramebuffer final
	{
	public:
		/**
		* Creates a framebuffer
		*/
		TFramebuffer(
			TDevice<ContextRegistry>& p_device,
			const data::FramebufferDesc<ContextRegistry>& p_desc
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
		ContextRegistry::FramebufferContext m_context;
	};
}
