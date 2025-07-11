/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/DeviceInfo.h>
#include <orhi/data/InstanceDesc.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/types/EGraphicsBackend.h>

#include <unordered_map>
#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	/**
	* Backend class that wraps the selected graphics API's context.
	*/
	template<typename BackendTraits>
	class TInstance final
	{
	public:
		/**
		* Creates the backend.
		* @param p_desc
		*/
		TInstance(const data::InstanceDesc& p_desc);

		/**
		* Destroys the backend.
		*/
		~TInstance();

		/**
		* Return the list of available devices to select from
		*/
		const std::vector<data::DeviceInfo>& GetSuitableDevices() const;

		/**
		* Create a logical device from the selected device ID
		* @param p_deviceId
		*/
		TDevice<BackendTraits>& CreateDevice(uint32_t p_deviceId);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

		/**
		* Returns a handle to the surface
		*/
		data::NativeHandle GetSurfaceHandle() const;

	private:
		BackendTraits::InstanceContext m_context;
	};
}
