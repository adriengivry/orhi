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
	* @brief The root object for managing graphics API instances and devices
	* 
	* TInstance represents the top-level graphics API context that manages
	* device enumeration, surface creation, and logical device creation.
	* It serves as the entry point for all graphics operations.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TInstance final
	{
	public:
		/**
		* @brief Creates a graphics instance with the specified configuration
		* @param p_desc Instance descriptor specifying application info, extensions, and validation layers
		*/
		TInstance(const data::InstanceDesc& p_desc);

		/**
		* @brief Destroys the graphics instance and releases all associated resources
		*/
		~TInstance();

		/**
		* @brief Gets the list of available physical devices
		* @return Vector of device information structures for all suitable devices
		*/
		const std::vector<data::DeviceInfo>& GetSuitableDevices() const;

		/**
		* @brief Creates a logical device from the specified physical device
		* @param p_deviceId Index of the physical device to create a logical device from
		* @return Reference to the created logical device
		*/
		TDevice<BackendTraits>& CreateDevice(uint32_t p_deviceId);

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying graphics instance
		*/
		data::NativeHandle GetNativeHandle() const;

		/**
		* @brief Gets the native handle to the presentation surface
		* @return Native handle to the underlying surface object
		*/
		data::NativeHandle GetSurfaceHandle() const;

	private:
		BackendTraits::InstanceContext m_context;
	};
}
