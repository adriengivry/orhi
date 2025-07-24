/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TPipelineLayout.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/ComPtr.h>
#include <orhi/impl/dx12/Device.h>

struct ID3D12RootSignature;

namespace orhi::impl::dx12
{
	struct PipelineLayoutContext 
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	};

	using PipelineLayout = api::TPipelineLayout<BackendTraits>;
}
