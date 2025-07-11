/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TSemaphore final
	{
	public:
		/**
		* Creates a semaphore
		*/
		TSemaphore(TDevice<BackendTraits>& p_device);

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
		BackendTraits::SemaphoreContext m_context;
	};
}
