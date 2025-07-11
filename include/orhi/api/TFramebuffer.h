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
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TFramebuffer final
	{
	public:
		/**
		* Creates a framebuffer
		*/
		TFramebuffer(
			TDevice<BackendTraits>& p_device,
			const data::FramebufferDesc<BackendTraits>& p_desc
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
		BackendTraits::FramebufferContext m_context;
	};
}
