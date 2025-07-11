/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/except/OutOfDateSwapChain.h>
#include <orhi/impl/vk/Queue.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/impl/vk/CommandBuffer.h>
#include <orhi/impl/vk/Semaphore.h>
#include <orhi/impl/vk/Fence.h>
#include <orhi/impl/vk/SwapChain.h>
#include <orhi/impl/vk/details/MemoryUtils.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Queue::TQueue(
		data::NativeHandle p_device,
		data::NativeHandle p_handle
	) : m_context{
		.device = p_device.As<VkDevice>(),
		.handle = p_handle.As<VkQueue>()
	}
	{

	}

	void Queue::Submit(
		std::initializer_list<std::reference_wrapper<CommandBuffer>> p_commandBuffers,
		std::initializer_list<std::reference_wrapper<Semaphore>> p_waitSemaphores,
		std::initializer_list<std::reference_wrapper<Semaphore>> p_signalSemaphores,
		std::optional<std::reference_wrapper<Fence>> p_fence
	)
	{
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		const auto waitSemaphores = details::MemoryUtils::PrepareArray<VkSemaphore>(p_waitSemaphores);
		const auto signalSemaphores = details::MemoryUtils::PrepareArray<VkSemaphore>(p_signalSemaphores);
		const auto commandBuffers = details::MemoryUtils::PrepareArray<VkCommandBuffer>(p_commandBuffers);

		VkSubmitInfo submitInfo{
			.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
			.waitSemaphoreCount = static_cast<uint32_t>(waitSemaphores.size()),
			.pWaitSemaphores = waitSemaphores.data(),
			.pWaitDstStageMask = waitStages,
			.commandBufferCount = static_cast<uint32_t>(commandBuffers.size()),
			.pCommandBuffers = commandBuffers.data(),
			.signalSemaphoreCount = static_cast<uint32_t>(signalSemaphores.size()),
			.pSignalSemaphores = signalSemaphores.data()
		};

		VkResult result = vkQueueSubmit(
			m_context.handle,
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
		const auto waitSemaphores = details::MemoryUtils::PrepareArray<VkSemaphore>(p_waitSemaphores);
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
			m_context.handle,
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

	template<>
	data::NativeHandle Queue::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

CTX_SIG_REG(TQueue, VULKAN, vk);

#endif // #if defined(ORHI_COMPILE_VULKAN)
