/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSemaphore.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/detail/ComPtr.h>
#include <orhi/impl/dx12/Device.h>

struct ID3D12Fence;

namespace orhi::impl::dx12
{
	struct SemaphoreContext
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	};

	using Semaphore = api::TSemaphore<BackendTraits>;
}
