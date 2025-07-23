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

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Queue::TQueue(
		Device& p_device,
		types::EQueueType p_queueType
	)
	{
		
	}

	template<>
	Queue::~TQueue()
	{
		
	}

	template<>
	void Queue::Submit(
		std::span<const CommandBuffer* const> p_commandBuffers,
		std::span<const data::SubmitSemaphoreInfo> p_waitSemaphores,
		std::span<const data::SubmitSemaphoreInfo> p_signalSemaphores,
		std::optional<std::reference_wrapper<Fence>> p_fence
	)
	{
		
	}

	template<>
	void Queue::Present(
		std::span<const data::PresentInfo> p_presentInfos,
		std::span<const Semaphore* const> p_waitSemaphores
	)
	{
		
	}

	template<>
	void Queue::WaitIdle()
	{
		
	}
}

template class orhi::api::TQueue<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
