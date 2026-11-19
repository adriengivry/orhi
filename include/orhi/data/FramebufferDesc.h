/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/math/Extent2D.h>
#include <orhi/types/EAttachmentType.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureAspectFlags.h>
#include <orhi/types/ETextureLayout.h>

#include <functional>
#include <initializer_list>

namespace orhi::api
{
	template<typename BackendTraits> class TDescriptor;
}

namespace orhi::data
{
	template<typename BackendTraits>
	struct FramebufferAttachmentDesc
	{
		std::reference_wrapper<api::TDescriptor<BackendTraits>> descriptor;
		types::EAttachmentType type = types::EAttachmentType::COLOR;
		types::EFormat format = types::EFormat::UNDEFINED;
		// UNDEFINED discards previous contents on entry and leaves the attachment layout unchanged on exit.
		types::ETextureLayout initialLayout = types::ETextureLayout::UNDEFINED;
		types::ETextureLayout finalLayout = types::ETextureLayout::UNDEFINED;
		types::ETextureAspectFlags aspectFlags = types::ETextureAspectFlags::NONE;
	};

	/**
	* @brief Descriptor for a set of dynamic-rendering attachments
	* 
	* Specifies the image views and extent used by a rendering operation.
	* 
	* @tparam BackendTraits Backend-specific traits defining implementation types
	*/
	template<typename BackendTraits>
	struct FramebufferDesc
	{
		std::initializer_list<FramebufferAttachmentDesc<BackendTraits>> attachments;
		math::Extent2D extent;
	};
}
