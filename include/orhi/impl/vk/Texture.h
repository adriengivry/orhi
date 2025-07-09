/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TTexture.h>
#include <orhi/impl/vk/Device.h>

struct VkImage_T;
typedef VkImage_T* VkImage;

struct VkDeviceMemory_T;
typedef VkDeviceMemory_T* VkDeviceMemory;

namespace orhi::impl::vk
{
	struct TextureContext
	{
		Device& device;
		VkImage handle;
		VkDeviceMemory memory;
		uint64_t allocatedBytes;
	};

	using Texture = api::TTexture<types::EGraphicsBackend::VULKAN, TextureContext, DeviceContext>;
}
