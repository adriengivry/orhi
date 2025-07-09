/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptor.h>
#include <orhi/impl/vk/Device.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureLayout.h>
#include <orhi/types/EDescriptorType.h>

namespace orhi::impl::vk
{
	enum class EVulkanDescriptorType
	{
		NONE = 0,
		BUFFER_VIEW,
		IMAGE_VIEW,
		SAMPLER,
		ACCELERATION_STRUCTURE
	};

	struct DescriptorContext
	{
		Device& device;
		data::NativeHandle handle;
		EVulkanDescriptorType type;
	};

	using Descriptor = api::TDescriptor<types::EGraphicsBackend::VULKAN, DescriptorContext, DeviceContext, TextureContext>;
}
