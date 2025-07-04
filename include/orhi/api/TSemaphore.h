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
	class TSemaphore final
	{
	public:
		/**
		* Creates a semaphore
		*/
		TSemaphore(TDevice<Backend, DeviceContext>& p_device);

		/**
		* Destroys the semaphore
		*/
		~TSemaphore();

		/**
		* Wait for semaphore
		* @param p_timeout
		*/
		void Wait(std::optional<uint64_t> p_timeout = std::nullopt);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		Context m_context;
	};
}
