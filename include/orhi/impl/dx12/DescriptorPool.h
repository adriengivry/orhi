/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorPool.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/DescriptorSet.h>
#include <orhi/impl/dx12/Device.h>

#include <deque>

namespace orhi::impl::dx12
{
	struct DescriptorPoolContext
	{
		Device& device;
		std::deque<DescriptorSet> descriptorSets;
	};

	using DescriptorPool = api::TDescriptorPool<BackendTraits>;
}
