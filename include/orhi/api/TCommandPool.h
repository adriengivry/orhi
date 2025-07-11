/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ECommandBufferLevel.h>
#include <orhi/types/EGraphicsBackend.h>

#include <vector>

namespace orhi::api
{
	template<typename BackendTraits> class TCommandBuffer;
	template<typename BackendTraits> class TDevice;

	template<typename BackendTraits>
	class TCommandPool final
	{
	public:
		/**
		* Creates a command pool
		*/
		TCommandPool(
			TDevice<BackendTraits>& p_device
		);

		/**
		* Destroys the command pool
		*/
		~TCommandPool();

		/**
		* Allocates a command buffer from the command pool
		*/
		std::vector<std::reference_wrapper<TCommandBuffer<BackendTraits>>> AllocateCommandBuffers(
			uint32_t p_count,
			types::ECommandBufferLevel p_level = types::ECommandBufferLevel::PRIMARY
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::CommandPoolContext m_context;
	};
}
