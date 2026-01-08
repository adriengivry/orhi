/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

namespace orhi::impl::dx12
{
	struct DescriptorSetLayoutContext
	{
		Device& device;
	};

	using DescriptorSetLayout = api::TDescriptorSetLayout<BackendTraits>;
}
