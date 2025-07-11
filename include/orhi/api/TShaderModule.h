/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

#include <span>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TShaderModule final
	{
	public:
		/**
		* Creates a shader module
		* @param p_device
		*/
		TShaderModule(
			TDevice<BackendTraits>& p_device,
			const std::span<const std::byte> p_source
		);

		/**
		* Destroys the shader module
		*/
		~TShaderModule();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::ShaderModuleContext m_context;
	};
}
