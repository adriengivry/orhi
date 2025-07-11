/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TCommandBuffer.h>
#include <orhi/types/ECommandBufferLevel.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, CTX_SIG_DCL>
	class TCommandPool final
	{
	public:
		/**
		* Creates a command pool
		*/
		TCommandPool(
			TDevice<Backend, CTX_SIG_FWD>& p_device
		);

		/**
		* Destroys the command pool
		*/
		~TCommandPool();

		/**
		* Allocates a command buffer from the command pool
		*/
		std::vector<std::reference_wrapper<TCommandBuffer<Backend, CTX_SIG_FWD>>> AllocateCommandBuffers(
			uint32_t p_count,
			types::ECommandBufferLevel p_level = types::ECommandBufferLevel::PRIMARY
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		CommandPoolContext m_context;
	};
}
