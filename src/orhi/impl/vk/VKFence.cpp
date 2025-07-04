/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/Fence.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	Fence::TFence(Device& p_device, bool p_createSignaled) :
		m_context{
			.device = p_device,
			.handle = VK_NULL_HANDLE
		}
	{
		VkFenceCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
			.flags = p_createSignaled ? VK_FENCE_CREATE_SIGNALED_BIT : VkFenceCreateFlags{}
		};

		VkResult result = vkCreateFence(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_context.handle
		);
		
		ORHI_ASSERT(result == VK_SUCCESS, "failed to create fence");
	}

	Fence::~TFence()
	{
		vkDestroyFence(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	void Fence::Wait(std::optional<uint64_t> p_timeout)
	{
		vkWaitForFences(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			1UL,
			&m_context.handle,
			VK_TRUE,
			p_timeout.value_or(std::numeric_limits<decltype(p_timeout)::value_type>::max())
		);
	}

	template<>
	void Fence::Reset()
	{
		vkResetFences(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			1,
			&m_context.handle
		);
	}

	template<>
	data::NativeHandle Fence::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

#endif // #if defined(ORHI_COMPILE_VULKAN)
