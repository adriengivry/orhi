/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EAttachmentType.h>
#include <orhi/types/EFormat.h>

namespace orhi::data
{
	/**
	* @brief Format and type of a graphics pipeline attachment
	* 
	* Describes the attachment formats used when creating a graphics pipeline
	* with dynamic rendering.
	*/
	struct AttachmentDesc
	{
		types::EAttachmentType type = types::EAttachmentType::COLOR; // Default to color attachment
		types::EFormat format;
	};
}
