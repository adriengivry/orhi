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
	template<typename ContextRegistry>
	class TSemaphore final
	{
	public:
		/**
		* Creates a semaphore
		*/
		TSemaphore(TDevice<ContextRegistry>& p_device);

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
		ContextRegistry::SemaphoreContext m_context;
	};
}
