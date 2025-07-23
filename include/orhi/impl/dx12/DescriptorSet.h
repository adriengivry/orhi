/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TDescriptorSet.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

#if defined(_WIN32)
#include <wrl.h>
#endif

struct ID3D12DescriptorHeap;

namespace orhi::impl::dx12
{
	struct DescriptorSetContext
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorSet;
	};

	using DescriptorSet = api::TDescriptorSet<BackendTraits>;
}
