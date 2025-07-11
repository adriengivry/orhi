/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#if defined(ORHI_COMPILE_VULKAN)

#include <orhi/impl/vk/Buffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/vk/details/MemoryUtils.h>
#include <orhi/impl/vk/details/Types.h>

#include <vulkan/vulkan.h>

using namespace orhi::impl::vk;

namespace orhi
{
	template<>
	Buffer::TBuffer(
		Device& p_device,
		const data::BufferDesc& p_desc
	) : m_context{
		.device = p_device,
		.handle = VK_NULL_HANDLE,
		.memory = VK_NULL_HANDLE,
		.allocatedBytes = 0ULL
	}
	{
		VkBufferCreateInfo bufferInfo{
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			.size = p_desc.size,
			.usage = utils::EnumToValue<VkBufferUsageFlags>(p_desc.usage),
			.sharingMode = VK_SHARING_MODE_EXCLUSIVE
		};

		VkResult result = vkCreateBuffer(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&bufferInfo,
			nullptr,
			&m_context.handle
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to create buffer!");
	}

	template<>
	Buffer::~TBuffer()
	{
		if (IsAllocated())
		{
			Deallocate();
		}

		vkDestroyBuffer(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			nullptr
		);
	}

	template<>
	bool Buffer::IsAllocated() const
	{
		return
			m_context.memory != VK_NULL_HANDLE &&
			m_context.allocatedBytes > 0;
	}

	template<>
	void Buffer::Allocate(types::EMemoryPropertyFlags p_properties)
	{
		ORHI_ASSERT(!IsAllocated(), "Buffer is already allocated");

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			&memRequirements
		);

		const auto memoryType = details::MemoryUtils::FindMemoryType(
			m_context.device.GetAdapterNativeHandle().As<VkPhysicalDevice>(),
			memRequirements.memoryTypeBits,
			utils::EnumToValue<VkMemoryPropertyFlags>(p_properties)
		);

		VkMemoryAllocateInfo allocInfo{
			.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
			.allocationSize = memRequirements.size,
			.memoryTypeIndex = memoryType
		};

		VkResult result = vkAllocateMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			&allocInfo,
			nullptr,
			&m_context.memory
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to allocate buffer memory!");

		vkBindBufferMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.handle,
			m_context.memory,
			0
		);

		m_context.allocatedBytes = memRequirements.size;
	}

	template<>
	void Buffer::Deallocate()
	{
		vkFreeMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.memory,
			nullptr
		);
	}

	template<>
	void Buffer::Upload(
		const void* p_data,
		std::optional<data::MemoryRange> p_memoryRange
	)
	{
		ORHI_ASSERT(IsAllocated(), "Uploading to unnallocated buffer");

		ORHI_ASSERT(
			!p_memoryRange.has_value() || p_memoryRange->offset + p_memoryRange->size <= m_context.allocatedBytes,
			"Uploading out of allocated buffer bounds"
		);

		const uint64_t offset = p_memoryRange.has_value() ? p_memoryRange->offset : 0;
		const uint64_t size = p_memoryRange.has_value() ? p_memoryRange->size : m_context.allocatedBytes;

		void* destPtr;
		VkResult result = vkMapMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.memory,
			offset,
			size,
			0,
			&destPtr
		);

		ORHI_ASSERT(result == VK_SUCCESS, "failed to map buffer memory!");

		std::memcpy(destPtr, p_data, size);

		vkUnmapMemory(
			m_context.device.GetNativeHandle().As<VkDevice>(),
			m_context.memory
		);
	}

	template<>
	uint64_t Buffer::GetAllocatedBytes() const
	{
		return m_context.allocatedBytes;
	}

	template<>
	data::NativeHandle Buffer::GetNativeHandle() const
	{
		return m_context.handle;
	}
}

template class orhi::api::TBuffer<orhi::impl::vk::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_VULKAN)
