/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TQueue.h>
#include <orhi/impl/dx12/BackendTraits.h>

#if defined(_WIN32)
#include <wrl.h>
#endif

struct ID3D12CommandQueue;

namespace orhi::impl::dx12
{
	struct QueueContext
	{
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue;
	};

	using Queue = api::TQueue<BackendTraits>;
}
