/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TPhysicalDevice.h>

namespace orhi::impl::vk
{
	struct PhysicalDeviceContext {};
	using PhysicalDevice = api::TPhysicalDevice<types::EGraphicsBackend::VULKAN, PhysicalDeviceContext>;
}
