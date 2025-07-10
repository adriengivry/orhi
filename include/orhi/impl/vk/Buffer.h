/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>
#include <orhi/impl/vk/Device.h>

struct VkBuffer_T;
typedef VkBuffer_T* VkBuffer;

struct VkDeviceMemory_T;
typedef VkDeviceMemory_T* VkDeviceMemory;

namespace orhi::impl::vk
{
	struct BufferContext
	{
		Device& device;
		VkBuffer handle;
		VkDeviceMemory memory;
		uint64_t allocatedBytes;
	};

	using Buffer = api::TBuffer<
		types::EGraphicsBackend::VULKAN,
		struct BufferContext,
		struct DeviceContext
	>;
}
