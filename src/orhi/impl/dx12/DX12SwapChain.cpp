/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/SwapChain.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/Descriptor.h>
#include <orhi/impl/dx12/Fence.h>
#include <orhi/impl/dx12/Semaphore.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	SwapChain::TSwapChain(
		Device& p_device,
		impl::common::NativeHandle p_surface,
		const math::Extent2D& p_windowSize,
		const data::SwapChainDesc& p_desc,
		std::optional<std::reference_wrapper<SwapChain>> p_oldSwapChain
	) : m_context {
			.device = p_device
		}
	{
		
	}

	template<>
	SwapChain::~TSwapChain()
	{
		
	}

	template<>
	uint32_t SwapChain::GetImageCount() const
	{
		return static_cast<uint32_t>(m_context.images.size());
	}

	template<>
	Descriptor& SwapChain::GetImageDescriptor(uint32_t p_index)
	{
		return m_context.imageDescriptors[p_index];
	}

	template<>
	uint32_t SwapChain::AcquireNextImage(
		std::optional<std::reference_wrapper<Semaphore>> p_semaphore,
		std::optional<std::reference_wrapper<Fence>> p_fence,
		std::optional<uint64_t> p_timeout
	)
	{
		return 0;
	}
}

template class orhi::api::TSwapChain<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
