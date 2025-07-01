/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TPhysicalDevice.h>

namespace orhi::impl::vk
{
	struct PhysicalDeviceContext {};
	using PhysicalDevice = apii::TPhysicalDevice<types::EGraphicsBackend::VULKAN, PhysicalDeviceContext>;
}
