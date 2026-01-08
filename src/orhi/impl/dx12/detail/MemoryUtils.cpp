/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/detail/MemoryUtils.h>

#include <orhi/debug/Assert.h>

namespace orhi::impl::dx12::detail
{
	D3D12_HEAP_TYPE MemoryUtils::GetBestHeapType(D3D12_RESOURCE_STATES p_initialState)
	{
		// For DX12, heap type selection is more straightforward
		// Most resources can use DEFAULT heap for GPU-only access
		// Use UPLOAD heap for CPU-to-GPU transfers
		// Use READBACK heap for GPU-to-CPU transfers
		
		if (p_initialState == D3D12_RESOURCE_STATE_GENERIC_READ)
		{
			return D3D12_HEAP_TYPE_UPLOAD;
		}
		else if (p_initialState == D3D12_RESOURCE_STATE_COPY_DEST)
		{
			return D3D12_HEAP_TYPE_READBACK;
		}

		return D3D12_HEAP_TYPE_DEFAULT;
	}
}

#endif // #if defined(ORHI_COMPILE_DX12)
