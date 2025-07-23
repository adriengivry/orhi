/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

#if defined(_WIN32)
#include <wrl.h>
#endif

struct ID3D12Resource;

namespace orhi::impl::dx12
{
	struct BufferContext
	{
		Device& device;
		Microsoft::WRL::ComPtr<ID3D12Resource> memory;
		uint64_t allocatedBytes;
	};

	using Buffer = api::TBuffer<BackendTraits>;
}
