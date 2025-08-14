/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSet.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/detail/DescriptorTypes.h>
#include <orhi/impl/dx12/Device.h>

#include <orhi/impl/dx12/detail/ComPtr.h>

#include <array>

namespace orhi::impl::dx12
{
	using DescriptorPool = api::TDescriptorPool<BackendTraits>;

	struct DescriptorSetContext
	{
		Device& device;
		DescriptorPool& pool;
		GPUDescriptorAddress rootConstantAddress;
		std::array<uint32_t, kDescriptorHeapTypeCount> heapOffsets;
	};

	using DescriptorSet = api::TDescriptorSet<BackendTraits>;
}
