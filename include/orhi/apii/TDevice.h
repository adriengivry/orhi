/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/SwapChainDesc.h>

namespace orhi::apii
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
		* Returns information about the swap chain
		* @param p_windowSize
		*/
		data::SwapChainDesc GetOptimalSwapChainDesc(std::pair<uint32_t, uint32_t> p_windowSize);

	private:
		Context m_context;
	};
}
