/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>
#include <orhi/impl/vk/BackendTraits.h>
#include <orhi/impl/vk/Device.h>

struct VkDeviceMemory_T;
typedef VkDeviceMemory_T* VkDeviceMemory;

namespace orhi::impl::vk
{
	struct BufferContext
	{
		Device& device;
		VkDeviceMemory memory;
		uint64_t allocatedBytes;
	};

	using Buffer = api::TBuffer<BackendTraits>;
}
