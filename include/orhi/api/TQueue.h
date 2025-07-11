/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

#include <optional>

namespace orhi::api
{
	template<typename BackendTraits> class TCommandBuffer;
	template<typename BackendTraits> class TFence;
	template<typename BackendTraits> class TSemaphore;
	template<typename BackendTraits> class TSwapChain;

	template<typename BackendTraits>
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
			std::initializer_list<std::reference_wrapper<TCommandBuffer<BackendTraits>>> p_commandBuffers,
			std::initializer_list<std::reference_wrapper<TSemaphore<BackendTraits>>> p_waitSemaphores = {},
			std::initializer_list<std::reference_wrapper<TSemaphore<BackendTraits>>> p_signalSemaphores = {},
			std::optional<std::reference_wrapper<TFence<BackendTraits>>> p_fence = std::nullopt
		);

		/**
		* Present the queue
		*/
		void Present(
			std::initializer_list<std::reference_wrapper<TSemaphore<BackendTraits>>> p_waitSemaphores,
			TSwapChain<BackendTraits>& p_swapChain,
			uint32_t p_swapChainIndice
		);

		/**
		* Returns the underlying object's native handle
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::QueueContext m_context;
	};
}
