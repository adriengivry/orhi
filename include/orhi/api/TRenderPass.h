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
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext>
	class TRenderPass final
	{
	public:
		/**
		* Creates a render pass using the give format
		* @param p_device
		* @param p_format
		*/
		TRenderPass(
			TDevice<Backend, DeviceContext>& p_device,
			types::EFormat p_format
		);

		/**
		* Destroys the render pass
		*/
		~TRenderPass();

	private:
		Context m_context;
	};
}
