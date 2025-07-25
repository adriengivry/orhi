/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#if defined(ORHI_COMPILE_DX12)

#include <orhi/impl/dx12/RenderPass.h>

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>
#include <orhi/impl/dx12/detail/Types.h>

#include <d3d12.h>
#include <dxgi1_6.h>

using namespace orhi::impl::dx12;

namespace orhi
{
	template<>
	RenderPass::TRenderPass(
		Device& p_device,
		std::initializer_list<data::AttachmentDesc> p_attachments
	) : m_context{
		.device = p_device
	}
	{
		
	}

	template<>
	RenderPass::~TRenderPass()
	{
		
	}
}

template class orhi::api::TRenderPass<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
