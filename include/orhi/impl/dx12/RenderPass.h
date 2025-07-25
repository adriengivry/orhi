/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry, Jian Bang Xu
* @licence: MIT
*/

#pragma once

#include <orhi/api/TRenderPass.h>
#include <orhi/impl/dx12/BackendTraits.h>
#include <orhi/impl/dx12/Device.h>
#include <orhi/data/AttachmentDesc.h>

#include <d3d12.h>
#include <dxgi1_6.h>
#include <vector>

namespace orhi::impl::dx12
{
	struct RenderPassContext
	{
		Device& device;

		// Since DX12 doesn't have render pass objects, we store the information
		D3D12_RT_FORMAT_ARRAY renderTargetFormats{};
		DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_UNKNOWN;
		std::vector<data::AttachmentDesc> attachments;
	};

	using RenderPass = api::TRenderPass<BackendTraits>;
}
