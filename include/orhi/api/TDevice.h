/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DeviceInfo.h>
#include <orhi/data/QueuesDesc.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/impl/common/BackendObject.h>
#include <orhi/math/Extent2D.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TQueue;

	/**
	* @brief A logical device representing a connection to a graphics adapter
	* 
	* TDevice encapsulates a logical device that provides access to GPU functionality.
	* It manages queues, memory allocation, and is required to create other graphics
	* objects like buffers, textures, pipelines, etc.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TDevice final : public impl::common::BackendObject
	{
	public:
		/**
		* @brief Creates a logical device (internal use - handled by the backend)
		* @param p_deviceInfo Information about the physical device
		* @param p_creationInfo Backend-specific creation parameters
		* @todo Make this constructor private
		*/
		TDevice(
			const data::DeviceInfo& p_deviceInfo,
			const void* p_creationInfo
		);

		/**
		* @brief Destroys the logical device and releases all associated resources
		*/
		~TDevice();

		/**
		* @brief Gets the graphics queue for rendering operations
		* @return Graphics queue object for submitting rendering commands
		*/
		TQueue<BackendTraits>& GetGraphicsQueue() const;

		/**
		* @brief Gets the present queue for displaying rendered images
		* @return Present queue object for presenting to the swap chain
		*/
		TQueue<BackendTraits>& GetPresentQueue() const;

		/**
		* @brief Gets optimal swap chain configuration for the specified window size
		* @param p_windowSize Window dimensions
		* @return Optimal swap chain descriptor with recommended settings
		*/
		data::SwapChainDesc GetOptimalSwapChainDesc(const math::Extent2D& p_windowSize);

		/**
		* @brief Gets information about available queue families
		* @return Descriptor containing available queue families and their properties
		*/
		data::QueuesDesc GetQueuesDesc() const;

		/**
		* @brief Waits for all operations on the device to complete
		* @note Blocks the calling thread until the device is idle
		*/
		void WaitIdle() const;

		/**
		* @brief Gets information about the physical device
		* @return Device information including capabilities, limits, and properties
		*/
		const data::DeviceInfo& GetInfo() const;

		/**
		* @brief Gets the native handle to the physical adapter
		* @return Native handle to the underlying physical adapter/device
		*/
		impl::common::NativeHandle GetAdapterNativeHandle() const;

	private:
		BackendTraits::DeviceContext m_context;
	};
}
