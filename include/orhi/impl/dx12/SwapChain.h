/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TSwapChain.h>
#include <orhi/data/SwapChainDesc.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/ComPtr.h>
#include <orhi/impl/dx12/Descriptor.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/impl/dx12/Framebuffer.h>

#include <deque>


struct IDXGISwapChain;
struct ID3D12Resource;

namespace orhi::impl::dx12
{
	struct SwapChainContext
	{
		Device& device;
		data::SwapChainDesc desc;
		std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> images;
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
		std::deque<Descriptor> imageDescriptors;
		math::Extent2D extent;
	};

	using SwapChain = api::TSwapChain<BackendTraits>;
}
