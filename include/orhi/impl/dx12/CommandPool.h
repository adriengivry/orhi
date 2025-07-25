/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TCommandPool.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/CommandBuffer.h>
#include <orhi/impl/dx12/Device.h>
#include "ComPtr.h"

#include <deque>

struct ID3D12CommandAllocator;

namespace orhi::impl::dx12
{
	struct CommandPoolContext
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	};

	using CommandPool = api::TCommandPool<BackendTraits>;
}
