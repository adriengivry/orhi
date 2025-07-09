/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TDevice.h>
#include <optional>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, class Context, class DeviceContext>
	class TFence final
	{
	public:
		/**
		* Creates a fence
		*/
		TFence(TDevice<Backend, DeviceContext>& p_device, bool p_createSignaled = false);

		/**
		* Destroys the fence
		*/
		~TFence();

		/**
		* Wait for fence
		* @param p_timeout
		*/
		void Wait(std::optional<uint64_t> p_timeout = std::nullopt);

		/**
		* Reset fence
		*/
		void Reset();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
