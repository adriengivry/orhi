/**
* @project: orhi (OpenRHI)
* @author: Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <stdint.h>

namespace orhi::impl::dx12
{
	using CPUDescriptorAddress = size_t;
	using GPUDescriptorAddress = uint64_t;
	enum class EDescriptorHeapType : uint32_t
	{
		CBV_SRV_UAV,
		SAMPLER,

		COUNT
	};
	constexpr size_t kDescriptorHeapTypeCount = static_cast<size_t>(EDescriptorHeapType::COUNT);
}
