/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Semaphore.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	Semaphore::TSemaphore(Device& p_device) :
		m_context{
			.device = p_device
	}
	{
		VkSemaphoreCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		};

		VkResult result = vkCreateSemaphore(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_handle.ReinterpretAs<VkSemaphore&>()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create semaphore");
	}

	Semaphore::~TSemaphore()
	{
		vkDestroySemaphore(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_handle.As<VkSemaphore>(),
			nullptr
		);
	}

	template<>
	void Semaphore::Wait(std::optional<uint64_t> p_timeout)
	{
		VkSemaphoreWaitInfo waitInfo{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
			.semaphoreCount = 1,
			.pSemaphores = &m_handle.ReinterpretAs<VkSemaphore&>()
		};

		vkWaitSemaphores(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&waitInfo,
			p_timeout.value_or(std::numeric_limits<decltype(p_timeout)::value_type>::max())
		);
	}
}

template class orhi::api::TSemaphore<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
