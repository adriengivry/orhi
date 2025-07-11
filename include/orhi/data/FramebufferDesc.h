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
	* @brief Descriptor for framebuffer creation
	* 
	* Specifies the configuration for creating a framebuffer, including
	* the render targets (attachments), associated render pass, and dimensions.
	* Framebuffers must be compatible with the render pass they're used with.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct FramebufferDesc
	{
		std::span<const NativeHandle> attachments;
		api::TRenderPass<BackendTraits>& renderPass;
		std::pair<uint32_t, uint32_t> extent;
	};
}
