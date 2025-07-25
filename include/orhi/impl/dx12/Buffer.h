/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TBuffer.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>

#include <orhi/impl/dx12/detail/ComPtr.h>

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
