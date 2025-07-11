/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <span>

#include <orhi/data/NativeHandle.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TRenderPass;
}

namespace orhi::data
{
	/**
	*
	*/
	template<typename BackendTraits>
	struct FramebufferDesc
	{
		std::span<const NativeHandle> attachments;
		api::TRenderPass<BackendTraits>& renderPass;
		std::pair<uint32_t, uint32_t> extent;
	};
}
