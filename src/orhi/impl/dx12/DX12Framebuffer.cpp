/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/Framebuffer.h>

#include <orhi/debug/Assert.h>
#include <orhi/impl/dx12/Descriptor.h>
#include <orhi/impl/dx12/RenderPass.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	Framebuffer::TFramebuffer(
		Device& p_device,
		const data::FramebufferDesc<BackendTraits>& p_desc
	) :
		m_context{
			.device = p_device
		}
	{
		
	}

	template<>
	Framebuffer::~TFramebuffer()
	{
		
	}
}

template class orhi::api::TFramebuffer<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
