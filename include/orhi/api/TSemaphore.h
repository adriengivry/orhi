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

	/**
	* @brief A synchronization primitive for GPU-GPU synchronization
	* 
	* TSemaphore provides a way to synchronize operations between different
	* command submissions on the GPU. Semaphores can be signaled by one
	* operation and waited on by another to ensure proper ordering.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TSemaphore final
	{
	public:
		/**
		* @brief Creates a semaphore in the unsignaled state
		* @param p_device Reference to the device that will own this semaphore
		*/
		TSemaphore(TDevice<BackendTraits>& p_device);

		/**
		* @brief Destroys the semaphore and releases associated resources
		*/
		~TSemaphore();

		/**
		* @brief Waits for the semaphore to become signaled
		* @param p_timeout Optional timeout in nanoseconds; if not provided, waits indefinitely
		*/
		void Wait(std::optional<uint64_t> p_timeout = std::nullopt);

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying semaphore object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::SemaphoreContext m_context;
	};
}
