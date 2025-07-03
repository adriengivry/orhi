/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <span>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/apii/TDevice.h>

namespace orhi::apii
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext>
	class TShaderModule final
	{
	public:
		/**
		* Creates a shader module
		* @param p_device
		*/
		TShaderModule(
			TDevice<Backend, DeviceContext>& p_device,
			const std::span<const std::byte> p_source
		);

		/**
		* Destroys the shader module
		*/
		virtual ~TShaderModule();

	private:
		Context m_context;
	};
}
