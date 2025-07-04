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

namespace orhi::api
{
	/**
	* Backend class that wraps the selected graphics API's context.
	*/
	template<types::EGraphicsBackend Backend, class Context>
	class TDevice final
	{
	public:
		/**
		* Creates the device (handled by the backend).
		* TODO: Make private
		*/
		TDevice(const void* p_deviceCreationDesc);

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
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

		/**
		* Returns the adapter's native handle
		*/
		data::NativeHandle GetAdapterNativeHandle() const;

	private:
		Context m_context;
	};
}
