/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <optional>
#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TFence final
	{
	public:
		/**
		* Creates a fence
		*/
		TFence(TDevice<BackendTraits>& p_device, bool p_createSignaled = false);

		/**
		* Destroys the fence
		*/
		~TFence();

		/**
		* Wait for fence
		* @param p_timeout
		*/
		void Wait(std::optional<uint64_t> p_timeout = std::nullopt);

		/**
		* Reset fence
		*/
		void Reset();

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::FenceContext m_context;
	};
}
