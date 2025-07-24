/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#if defined(ORHI_COMPILE_DX12)

#include <d3d12.h>
#include <dxgi1_4.h>

#include <span>
#include <string>
#include <vector>

namespace orhi::impl::dx12::detail
{
	struct DeviceCreationInfo
	{
		IDXGIAdapter1* adapter = nullptr;
		DXGI_ADAPTER_DESC1 adapterDesc{};
		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_12_0;
		UINT nodeIndex = 0;
	};
}

#endif // #if defined(ORHI_COMPILE_DX12)
