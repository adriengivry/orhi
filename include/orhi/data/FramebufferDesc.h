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
	template<typename ContextRegistry>
	struct FramebufferDesc
	{
		std::span<const NativeHandle> attachments;
		api::TRenderPass<ContextRegistry>& renderPass;
		std::pair<uint32_t, uint32_t> extent;
	};
}
