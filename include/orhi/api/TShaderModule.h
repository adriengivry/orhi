/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <span>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TDevice.h>
#include <orhi/data/NativeHandle.h>

namespace orhi::api
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

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
