/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TDevice.h>

namespace orhi::impl::vk
{
	struct DeviceContext {};
	using Device = apii::TDevice<types::EGraphicsBackend::VULKAN, DeviceContext>;
}
