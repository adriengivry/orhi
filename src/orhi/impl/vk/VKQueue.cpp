/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Queue.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/except/OutOfDateSwapChain.h>
#include <orhi/impl/vk/detail/MemoryUtils.h>
#include <orhi/impl/vk/detail/Types.h>
#include <orhi/impl/vk/CommandBuffer.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/Fence.h>
#include <orhi/impl/vk/Semaphore.h>
#include <orhi/impl/vk/SwapChain.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Queue::TQueue(
		impl::common::NativeHandle p_device,
		impl::common::NativeHandle p_handle
	) : BackendObject(p_handle),
		m_context{
		.device = p_device.As<VkDevice>()
	}
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
		std::vector<VkPipelineStageFlags> waitStages;
		waitStages.reserve(p_waitStages.size());
		for (const auto stage : p_waitStages)
		{
			waitStages.push_back(utils::EnumToValue<VkPipelineStageFlags>(stage));
		}

		const auto waitSemaphores = detail::MemoryUtils::PrepareArray<VkSemaphore>(p_waitSemaphores);
		const auto signalSemaphores = detail::MemoryUtils::PrepareArray<VkSemaphore>(p_signalSemaphores);
		const auto commandBuffers = detail::MemoryUtils::PrepareArray<VkCommandBuffer>(p_commandBuffers);

		VkSubmitInfo submitInfo{
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
			.pWaitSemaphores = waitSemaphores.data(),
			.pWaitDstStageMask = waitStages.data(),
			.commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
			.pCommandBuffers = commandBuffers.data(),
			.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size()),
			.pSignalSemaphores = signalSemaphores.data()
		};

		VkResult result = vkQueueSubmit(
			m_handle.As<VkQueue>(),
			1,
			&submitInfo,
			p_fence.has_value() ? p_fence.value().get().GetNativeHandle().As<VkFence>() : VK_NULL_HANDLE
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to submit queue!");
	}

	void Queue::Present(
		std::initializer_list<std::reference_wrapper<Semaphore>> p_waitSemaphores,
		SwapChain& p_swapChain,
		uint32_t p_swapChainIndice
	)
	{
		const auto waitSemaphores = detail::MemoryUtils::PrepareArray<VkSemaphore>(p_waitSemaphores);
		const auto swapChainHandle = p_swapChain.GetNativeHandle().As<VkSwapchainKHR>();

		VkPresentInfoKHR presentInfo{
			.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
			.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
			.pWaitSemaphores = waitSemaphores.data(),
			.swapchainCount = 1,
			.pSwapchains = &swapChainHandle,
			.pImageIndices = &p_swapChainIndice,
			.pResults = nullptr // (optional) allows to specify an array of VkResult values to check for every individual swap chain if presentation was successful. 
		};

		// Note: there is an error with our semaphores that can be addressed with:
		// https://docs.vulkan.org/guide/latest/swapchain_semaphore_reuse.html
		// It seems like the debug validation layer didn't use to pick up this error when vulkan-tutorial was written.
		VkResult result = vkQueuePresentKHR(
			m_handle.As<VkQueue>(),
			&presentInfo
		);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			throw except::OutOfDateSwapChain();
		}

		ORHI_ASSERT(result == VK_SUCCESS, "failed to submit queue!");
	}

	template<>
	Queue::~TQueue()
	{

	}
}

template class orhi::api::TQueue<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
