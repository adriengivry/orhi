/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <initializer_list>

#include <orhi/impl/common/NativeHandle.h>
#include <orhi/math/Extent2D.h>
#include <orhi/types/EGraphicsBackend.h>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptor;
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
		std::initializer_list<std::reference_wrapper<api::TDescriptor<BackendTraits>>> attachments;
		api::TRenderPass<BackendTraits>& renderPass;
		math::Extent2D extent;
	};
}
