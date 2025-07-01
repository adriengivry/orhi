/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/DeviceInfo.h>
#include <orhi/data/BackendDesc.h>

namespace orhi::apii
{
	/**
	* Backend class that wraps the selected graphics API's context.
	*/
	template<types::EGraphicsBackend Backend, class Context>
	class TBackend final
	{
	public:
		/**
		* Creates the backend.
		* @param p_desc
		*/
		TBackend(const data::BackendDesc& p_desc);

		/**
		* Destroys the backend.
		*/
		~TBackend();

		/**
		* Return the list of available devices to select from
		*/
		const std::vector<data::DeviceInfo>& GetSuitableDevices() const;

		/**
		* Select a device to use given its Id
		* @param p_deviceId
		*/
		void SelectDevice(uint32_t p_deviceId);

		/**
		* Returns true if the backend is in a valid state
		*/
		bool Validate() const;

	private:
		Context m_context;
	};
}
