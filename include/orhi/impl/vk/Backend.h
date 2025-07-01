/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <memory>
#include <orhi/apii/TBackend.h>

struct VkInstance_T;
typedef VkInstance_T* VkInstance;

namespace orhi::impl::vk
{
	struct BackendContext 
	{
		VkInstance instance;
	};

	using Backend = apii::TBackend<types::EGraphicsBackend::VULKAN, BackendContext>;
}
