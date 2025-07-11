/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EGraphicsBackend.h>
#include <orhi/data/NativeHandle.h>
#include <orhi/api/TSwapChain.h>
#include <orhi/api/TCommandBuffer.h>

namespace orhi::api
{
	template<types::EGraphicsBackend Backend, typename ContextRegistry>
	class TQueue final
	{
	public:
		/**
		* Creates a queue from its native handle
		* @note for device use
		*/
		TQueue(
			data::NativeHandle p_device,
			data::NativeHandle p_handle
		);

		/**
		* Destroys the queue
		*/
		~TQueue();

		/**
		* Submit the queue
		*/
		void Submit(
			std::initializer_list<std::reference_wrapper<TCommandBuffer<Backend, ContextRegistry>>> p_commandBuffers,
			std::initializer_list<std::reference_wrapper<TSemaphore<Backend, ContextRegistry>>> p_waitSemaphores = {},
			std::initializer_list<std::reference_wrapper<TSemaphore<Backend, ContextRegistry>>> p_signalSemaphores = {},
			std::optional<std::reference_wrapper<TFence<Backend, ContextRegistry>>> p_fence = std::nullopt
		);

		/**
		* Present the queue
		*/
		void Present(
			std::initializer_list<std::reference_wrapper<TSemaphore<Backend, ContextRegistry>>> p_waitSemaphores,
			TSwapChain<Backend, ContextRegistry>& p_swapChain,
			uint32_t p_swapChainIndice
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		ContextRegistry::QueueContext m_context;
	};
}
