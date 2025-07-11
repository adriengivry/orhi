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

	/**
	* @brief A queue for submitting commands to the GPU
	* 
	* TQueue represents a command queue that can execute command buffers on the GPU.
	* Queues can be specialized for different types of operations (graphics, compute, transfer)
	* and provide synchronization through semaphores and fences.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	class TQueue final
	{
	public:
		/**
		* @brief Creates a queue from native handles (internal use by device)
		* @param p_device Native handle to the logical device
		* @param p_handle Native handle to the underlying queue object
		*/
		TQueue(
			data::NativeHandle p_device,
			data::NativeHandle p_handle
		);

		/**
		* @brief Destroys the queue object
		*/
		~TQueue();

		/**
		* @brief Submits command buffers to the queue for execution
		* @param p_commandBuffers List of command buffers to execute
		* @param p_waitSemaphores List of semaphores to wait on before execution
		* @param p_signalSemaphores List of semaphores to signal after execution
		* @param p_fence Optional fence to signal when execution completes
		*/
		void Submit(
			std::initializer_list<std::reference_wrapper<TCommandBuffer<BackendTraits>>> p_commandBuffers,
			std::initializer_list<std::reference_wrapper<TSemaphore<BackendTraits>>> p_waitSemaphores = {},
			std::initializer_list<std::reference_wrapper<TSemaphore<BackendTraits>>> p_signalSemaphores = {},
			std::optional<std::reference_wrapper<TFence<BackendTraits>>> p_fence = std::nullopt
		);

		/**
		* @brief Presents a swap chain image to the screen
		* @param p_waitSemaphores List of semaphores to wait on before presenting
		* @param p_swapChain The swap chain containing the image to present
		* @param p_swapChainIndice Index of the swap chain image to present
		*/
		void Present(
			std::initializer_list<std::reference_wrapper<TSemaphore<BackendTraits>>> p_waitSemaphores,
			TSwapChain<BackendTraits>& p_swapChain,
			uint32_t p_swapChainIndice
		);

		/**
		* @brief Gets the native handle for backend-specific operations
		* @return Native handle to the underlying queue object
		*/
		data::NativeHandle GetNativeHandle() const;

	private:
		BackendTraits::QueueContext m_context;
	};
}
