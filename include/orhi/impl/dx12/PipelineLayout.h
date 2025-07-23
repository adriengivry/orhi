/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TPipelineLayout.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

#if defined(_WIN32)
#include <wrl.h>
#endif

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
