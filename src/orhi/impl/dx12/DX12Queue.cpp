/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Queue.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>
#include <orhi/impl/dx12/CommandBuffer.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/impl/dx12/Fence.h>
#include <orhi/impl/dx12/Semaphore.h>
#include <orhi/impl/dx12/SwapChain.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Queue::TQueue(
		impl::common::NativeHandle p_device,
		impl::common::NativeHandle p_handle
	) : BackendObject(p_handle),
		m_context {
			
		}
	{
		
	}

	template<>
	Queue::~TQueue()
	{
		
	}

	void Queue::Submit(
		std::initializer_list<std::reference_wrapper<CommandBuffer>> p_commandBuffers,
		std::initializer_list<std::reference_wrapper<Semaphore>> p_waitSemaphores,
		std::initializer_list<types::EPipelineStageFlags> p_waitStages,
		std::initializer_list<std::reference_wrapper<Semaphore>> p_signalSemaphores,
		std::optional<std::reference_wrapper<Fence>> p_fence
	)
	{
		
	}

	void Queue::Present(
		std::initializer_list<std::reference_wrapper<Semaphore>> p_waitSemaphores,
		SwapChain& p_swapChain,
		uint32_t p_swapChainIndice
	)
	{
		
	}
}

template class orhi::api::TQueue<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
