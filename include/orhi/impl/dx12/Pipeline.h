/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TPipeline.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/impl/dx12/detail/ComPtr.h>

struct ID3D12PipelineState;

namespace orhi::impl::dx12
{
	struct PipelineContext 
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	};

	using Pipeline = api::TPipeline<BackendTraits>;
}
