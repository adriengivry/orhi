/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TInstance.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/ComPtr.h>

#include <memory>

struct IDXGIFactory5;
struct IDXGIAdapter1;

namespace orhi::impl::dx12
{
	struct InstanceContext
	{
		Microsoft::WRL::ComPtr<IDXGIFactory5> dxgiFactory;
		Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
		HWND surface;
	};

	using Instance = api::TInstance<BackendTraits>;
}
