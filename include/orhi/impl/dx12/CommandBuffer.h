/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>
#include <orhi/impl/dx12/BackendTraits.h>

struct ID3D12GraphicsCommandList;

namespace orhi::impl::dx12
{
	struct CommandBufferContext
	{
		
	};
	using CommandBuffer = api::TCommandBuffer<BackendTraits>;
}
