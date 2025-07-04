/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <span>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TRenderPass.h>

namespace orhi::data
{
	/**
	*
	*/
	template<types::EGraphicsBackend Backend, class DeviceContext, class RenderPassContext>
	struct FramebufferDesc
	{
		std::span<const NativeHandle> attachments;
		api::TRenderPass<Backend, RenderPassContext, DeviceContext>& renderPass;
		std::pair<uint32_t, uint32_t> extent;
	};
}
