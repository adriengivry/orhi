/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TDeviceManager.h>

namespace orhi::impl::vk
{
	struct DeviceManagerContext {};
	using DeviceManager = apii::TDeviceManager<types::EGraphicsBackend::VULKAN, DeviceManagerContext>;
}
