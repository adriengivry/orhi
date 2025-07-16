/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/detail/Object.h>
#include <orhi/types/EGraphicsBackend.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* @brief A synchronization primitive for CPU-GPU synchronization
	* 
	* TFence provides a way for the CPU to wait for GPU operations to complete.
	* Fences can be signaled by the GPU when command execution finishes,
	* allowing the CPU to synchronize with GPU work.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TFence final : public detail::Object
	{
	public:
		/**
		* @brief Creates a fence in the specified initial state
		* @param p_device Reference to the device that will own this fence
		* @param p_createSignaled If true, creates the fence in a signaled state; otherwise creates it in an unsignaled state
		*/
		TFence(TDevice<BackendTraits>& p_device, bool p_createSignaled = false);

		/**
		* @brief Destroys the fence and releases associated resources
		*/
		~TFence();

		/**
		* @brief Waits for the fence to become signaled
		* @param p_timeout Optional timeout in nanoseconds; if not provided, waits indefinitely
		*/
		void Wait(std::optional<uint64_t> p_timeout = std::nullopt);

		/**
		* @brief Resets the fence to the unsignaled state
		* @note The fence must be signaled before it can be reset
		*/
		void Reset();

	private:
		BackendTraits::FenceContext m_context;
	};
}
