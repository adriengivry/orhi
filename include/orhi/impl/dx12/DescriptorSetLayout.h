/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSetLayout.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/impl/dx12/detail/DescriptorTypes.h>

#include <array>

namespace orhi::impl::dx12
{
	struct DescriptorRangeMapping final
	{
		EDescriptorHeapType heapType;
		uint32_t heapOffset;
		uint32_t descriptorIndex;
	};

	struct RootConstantMapping final
	{
		uint16_t rootConstantCount;
		uint16_t rootOffset;
	};

	struct DescriptorSetLayoutContext
	{
		Device& device;
		std::array<uint32_t, kDescriptorHeapTypeCount> descriptorIndices;
		std::vector<DescriptorRangeMapping> descriptorRanges;
		RootConstantMapping rootConstantMapping;
	};

	using DescriptorSetLayout = api::TDescriptorSetLayout<BackendTraits>;
}
