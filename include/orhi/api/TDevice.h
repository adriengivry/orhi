/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/QueuesDesc.h>
#include <orhi/data/DeviceInfo.h>
#include <orhi/api/TContextRegistry.h>

namespace orhi::api
{
	/**
	* Backend class that wraps the selected graphics API's context.
	*/
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TDevice final
	{
	public:
		/**
		* Creates the device (handled by the backend).
		* TODO: Make private
		*/
		TDevice(
			const data::DeviceInfo& p_deviceInfo,
			const void* p_creationInfo
		);

		/**
		* Destroys the backend.
		*/
		~TDevice();

		/**
		* Returns the graphics queue associated with this logical device
		* @note doesn't return a native handle, but an actual handle
		*/
		data::NativeHandle GetGraphicsQueue() const;

		/**
		* Returns the present queue associated with this logical device
		* @note doesn't return a native handle, but an actual handle
		*/
		data::NativeHandle GetPresentQueue() const;

		/**
		* Returns information about the swap chain
		* @param p_windowSize
		*/
		data::SwapChainDesc GetOptimalSwapChainDesc(std::pair<uint32_t, uint32_t> p_windowSize);

		/**
		* Returns information about available queues for this device
		*/
		data::QueuesDesc GetQueuesDesc() const;

		/**
		* Wait idle
		*/
		void WaitIdle() const;

		/**
		* Returns the device info
		*/
		const data::DeviceInfo& GetInfo() const;

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

		/**
		* Returns the adapter's native handle
		*/
		data::NativeHandle GetAdapterNativeHandle() const;

	private:
		ContextRegistry::DeviceContext m_context;
	};
}
