/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorPool.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/DescriptorSet.h>
#include <orhi/impl/dx12/detail/DescriptorTypes.h>
#include <orhi/impl/dx12/Device.h>

#include <orhi/impl/dx12/detail/ComPtr.h>

#include <array>

struct ID3D12DescriptorHeap;

namespace orhi::impl::dx12
{
	struct DescriptorPoolContext
	{
		Device& device;
		std::array<Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>, kDescriptorHeapTypeCount> descriptorHeaps;
		std::array<uint32_t, kDescriptorHeapTypeCount> descriptorSize;
		std::vector<DescriptorSet> descriptorSets;
		std::vector<GPUDescriptorAddress> rootConstants;
		uint32_t descriptorHeapCount = 0;
		uint32_t descriptorSetCount = 0;
		uint32_t rootConstantCount = 0;
	};

	using DescriptorPool = api::TDescriptorPool<BackendTraits>;
}
