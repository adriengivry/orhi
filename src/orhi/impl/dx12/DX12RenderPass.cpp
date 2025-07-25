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
#include <orhi/utils/EnumMapper.h>
#include <orhi/types/EAttachmentType.h>

#include <d3d12.h>
#include <dxgi1_6.h>

#include <unordered_map>
#include <vector>

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
		// DirectX 12 doesn't have a render pass object like Vulkan
		// Instead, we store the attachment information for later use in pipeline creation
		std::unordered_map<types::EAttachmentType, std::vector<data::AttachmentDesc>> attachmentsByType;
		
		// Initialize attachment type containers
		attachmentsByType[types::EAttachmentType::COLOR] = {};
		attachmentsByType[types::EAttachmentType::DEPTH_STENCIL] = {};
		attachmentsByType[types::EAttachmentType::RESOLVE] = {};

		for (const auto& attachment : p_attachments)
		{
			attachmentsByType[attachment.type].push_back(attachment);
		}

		ORHI_ASSERT(
			attachmentsByType[types::EAttachmentType::DEPTH_STENCIL].size() <= 1,
			"Only one depth/stencil attachment is allowed per render pass."
		);

		ORHI_ASSERT(
			attachmentsByType[types::EAttachmentType::COLOR].size() <= D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT,
			"Too many color attachments. DirectX 12 supports a maximum of 8 simultaneous render targets."
		);

		m_context.renderTargetFormats.NumRenderTargets = static_cast<UINT>(attachmentsByType[types::EAttachmentType::COLOR].size());
		
		for (size_t i = 0; i < attachmentsByType[types::EAttachmentType::COLOR].size(); ++i)
		{
			const auto& colorAttachment = attachmentsByType[types::EAttachmentType::COLOR][i];
			m_context.renderTargetFormats.RTFormats[i] = utils::EnumToValue<DXGI_FORMAT>(colorAttachment.format);
		}

		// Fill remaining slots with DXGI_FORMAT_UNKNOWN
		for (size_t i = attachmentsByType[types::EAttachmentType::COLOR].size(); i < D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
		{
			m_context.renderTargetFormats.RTFormats[i] = DXGI_FORMAT_UNKNOWN;
		}

		if (!attachmentsByType[types::EAttachmentType::DEPTH_STENCIL].empty())
		{
			const auto& depthAttachment = attachmentsByType[types::EAttachmentType::DEPTH_STENCIL][0];
			m_context.depthStencilFormat = utils::EnumToValue<DXGI_FORMAT>(depthAttachment.format);
		}
		else
		{
			m_context.depthStencilFormat = DXGI_FORMAT_UNKNOWN;
		}

		m_context.attachments.reserve(p_attachments.size());
		for (const auto& attachment : p_attachments)
		{
			m_context.attachments.push_back(attachment);
		}

		// Since DirectX 12 doesn't have a render pass handle, we store a dummy value
		// The actual render pass information is contained in the context member variables above
		m_handle = reinterpret_cast<void*>(0x1); // Non-null dummy handle to indicate valid state
	}

	template<>
	RenderPass::~TRenderPass()
	{
	}
}

template class orhi::api::TRenderPass<orhi::impl::dx12::BackendTraits>;

#endif // #if defined(ORHI_COMPILE_DX12)
