/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/SwapChain.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	SwapChain::TSwapChain(
		Device& p_device,
		const data::SwapChainDesc& p_desc
	)
	{
		
	}

	template<>
	SwapChain::~TSwapChain()
	{
		
	}

	template<>
	void SwapChain::AcquireNextTexture(
		std::optional<std::reference_wrapper<Semaphore>> p_semaphore,
		std::optional<std::reference_wrapper<Fence>> p_fence
	)
	{
		
	}

	template<>
	uint32_t SwapChain::GetCurrentTextureIndex() const
	{
		return 0;
	}

	template<>
	Texture& SwapChain::GetTexture(uint32_t p_index)
	{
		static Texture* texture = nullptr;
		return *texture;
	}

	template<>
	uint32_t SwapChain::GetTextureCount() const
	{
		return 0;
	}

	template<>
	const math::Extent2D& SwapChain::GetExtent() const
	{
		static math::Extent2D extent;
		return extent;
	}
}

template class orhi::api::TSwapChain<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
