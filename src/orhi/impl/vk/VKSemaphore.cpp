/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Semaphore.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	Semaphore::TSemaphore(Device& p_device) :
		m_context{
			.device = p_device,
			.handle = VK_NULL_HANDLE
	}
	{
		VkSemaphoreCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
		};

		VkResult result = vkCreateSemaphore(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_context.handle
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create semaphore");
	}

	Semaphore::~TSemaphore()
	{
		vkDestroySemaphore(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	void Semaphore::Wait(std::optional<uint64_t> p_timeout)
	{
		VkSemaphoreWaitInfo waitInfo{
			.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO,
			.semaphoreCount = 1,
			.pSemaphores = &m_context.handle
		};

		vkWaitSemaphores(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&waitInfo,
			p_timeout.value_or(std::numeric_limits<decltype(p_timeout)::value_type>::max())
		);
	}

	template<>
	data::NativeHandle Semaphore::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

CTX_SIG_REG_VK(TSemaphore);

#endif // #if defined(ORHI_COMPILE_VULKAN)
