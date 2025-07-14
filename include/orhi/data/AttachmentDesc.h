/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EAttachmentType.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureLayout.h>

namespace orhi::data
{
	/**
	* @brief Descriptor for an attachment in a render pass
	* 
	* Describes the properties of an attachment used in a render pass.
	* Can be used to specify color, depth, or stencil attachments.
	*/
	struct AttachmentDesc
	{
		types::EAttachmentType type = types::EAttachmentType::COLOR; // Default to color attachment
		types::EFormat format;
		types::ETextureLayout initialLayout = types::ETextureLayout::UNDEFINED;
		types::ETextureLayout finalLayout = types::ETextureLayout::UNDEFINED;
	};
}
