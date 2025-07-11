/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/CommandBuffer.h>
#include <orhi/impl/vk/CommandPool.h>
#include <orhi/impl/vk/details/Types.h>
#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	CommandPool::TCommandPool(
		Device& p_device
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE
	}
	{
		VkCommandPoolCreateInfo createInfo{
			.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
			.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
			// TODO: Replace with actual graphics queue family index
			.queueFamilyIndex = m_context.device.GetQueuesDesc().indices.front()
		};

		VkResult result = vkCreateCommandPool(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&createInfo,
			nullptr,
			&m_context.handle
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create command pool");
	}

	template<>
	CommandPool::~TCommandPool()
	{
		vkDestroyCommandPool(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	std::vector<std::reference_wrapper<CommandBuffer>> CommandPool::AllocateCommandBuffers(
		uint32_t p_count,
		types::ECommandBufferLevel p_level
	)
	{
		std::vector<std::reference_wrapper<CommandBuffer>> output;
		output.reserve(p_count);

		VkCommandBufferAllocateInfo allocInfo{
			.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
			.commandPool = m_context.handle,
			.level = utils::EnumToValue<VkCommandBufferLevel>(p_level),
			.commandBufferCount = p_count
		};

		std::vector<VkCommandBuffer> allocatedCommandBuffers(p_count);

		VkResult result = vkAllocateCommandBuffers(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&allocInfo,
			allocatedCommandBuffers.data()
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to allocate command buffer!");

		for (auto allocatedCommandBuffer : allocatedCommandBuffers)
		{
			output.emplace_back(
				m_context.commandBuffers.emplace_back(CommandBuffer{
					allocatedCommandBuffer
				})
			);
		}

		return output;
	}

	template<>
	data::NativeHandle CommandPool::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

template class orhi::api::TCommandPool<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
