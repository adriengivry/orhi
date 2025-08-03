/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/DescriptorPool.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/DescriptorSetLayout.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	DescriptorPool::TDescriptorPool(
		Device& p_device,
		const data::DescriptorPoolDesc& p_desc
	) : m_context{
		.device = p_device,
	}
	{
		ORHI_ASSERT(p_desc.maxSets > 0, "Max set count must be > 0");
		ORHI_ASSERT(!p_desc.poolSizes.empty(), "Pool sizes cannot be empty");

		std::array<uint32_t, kDescriptorHeapTypeCount> descriptorHeapSize{};

		for (const auto& poolSize : p_desc.poolSizes)
		{
			ORHI_ASSERT(poolSize.descriptorCount > 0, "Descriptor count must be > 0");

			size_t index = static_cast<size_t>(utils::EnumToValue<D3D12_DESCRIPTOR_HEAP_TYPE>(poolSize.type));
			descriptorHeapSize[index] += poolSize.descriptorCount;
		}

		ID3D12Device* device = p_device.GetNativeHandle().As<ID3D12Device*>();
		for (size_t i = 0; i < kDescriptorHeapTypeCount; ++i)
		{
			if (descriptorHeapSize[i] > 0)
			{
				D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
				heapDesc.Type = static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(i);
				heapDesc.NumDescriptors = descriptorHeapSize[i];
				heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
				heapDesc.NodeMask = 0;
				Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap;
				HRESULT hr = device->CreateDescriptorHeap(
					&heapDesc,
					IID_PPV_ARGS(&descriptorHeap)
				);
				ORHI_ASSERT(SUCCEEDED(hr), "Failed to create descriptor heap");
				m_context.descriptorHeaps[m_context.descriptorHeapCount] = std::move(descriptorHeap);
				m_context.descriptorSize[m_context.descriptorHeapCount] = device->GetDescriptorHandleIncrementSize(static_cast<D3D12_DESCRIPTOR_HEAP_TYPE>(i));
				++m_context.descriptorHeapCount;
			}
		}

		m_context.descriptorSets.resize(p_desc.maxSets);
		m_context.rootConstants.resize(p_desc.maxSets);
	}

	template<>
	DescriptorPool::~TDescriptorPool()
	{
		
	}

	template<>
	std::vector<std::reference_wrapper<DescriptorSet>> DescriptorPool::AllocateDescriptorSets(
		const DescriptorSetLayout& p_layout,
		uint32_t p_count
	)
	{
		ORHI_ASSERT(m_context.descriptorSetCount + p_count < m_context.descriptorSets.size(), "Failed to allocate descriptor set");
		std::vector<std::reference_wrapper<DescriptorSet>> output;
		output.reserve(p_count);

		for (uint32_t i = 0; i < p_count; ++i)
		{

		}

		return output;
	}
}

template class orhi::api::TDescriptorPool<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
