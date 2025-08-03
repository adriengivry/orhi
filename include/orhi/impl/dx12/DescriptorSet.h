/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSet.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/DescriptorPool.h>
#include <orhi/impl/dx12/detail/DescriptorTypes.h>
#include <orhi/impl/dx12/Device.h>

#include <orhi/impl/dx12/detail/ComPtr.h>

namespace orhi::impl::dx12
{
	struct DescriptorSetContext
	{
		Device& device;
		DescriptorPool& pool;
		std::array<uint32_t, kDescriptorHeapTypeCount> heapOffsets;
	};

	using DescriptorSet = api::TDescriptorSet<BackendTraits>;
}
