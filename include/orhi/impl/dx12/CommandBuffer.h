/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandBuffer.h>
#include <orhi/impl/dx12/BackendTraits.h>

#include <orhi/impl/dx12/Device.h>
#include <orhi/impl/dx12/CommandPool.h>

#include "ComPtr.h"

struct ID3D12GraphicsCommandList;

namespace orhi::impl::dx12
{
	struct CommandBufferContext
	{
		Device& device;
		CommandPool& commandPool;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	};
	using CommandBuffer = api::TCommandBuffer<BackendTraits>;
}
