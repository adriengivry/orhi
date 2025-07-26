/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptor.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/types/EDescriptorType.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureLayout.h>
#include <orhi/types/EBufferViewType.h>

struct ID3D12Resource;

namespace orhi::impl::dx12
{
	using CPUDescriptorAddress = size_t;
	using GPUDescriptorAddress = uint64_t;

	enum class EDescriptorHeapType : uint32_t
	{
		CBV_SRV_UAV,
		SAMPLER,
	};

	struct DescriptorHandle
	{
		static constexpr uint64_t kHeapTypeBitCount = 2;
		static constexpr uint64_t kHeapIndexBitCount = 16;
		static constexpr uint64_t kHeapOffsetBitCount = 14;

		EDescriptorHeapType heapType : kHeapTypeBitCount;
		uint32_t heapIndex : kHeapIndexBitCount;
		uint32_t heapOffset : kHeapIndexBitCount;
	};

	struct DescriptorContext
	{
		Device& device;
		ID3D12Resource* resource = nullptr;
		CPUDescriptorAddress cpuAddress = 0;
		GPUDescriptorAddress gpuAddress = 0;
		types::EBufferViewType type;
		DescriptorHandle handle;
		bool isIntegerFormat = false;
	};

	using Descriptor = api::TDescriptor<BackendTraits>;
}
