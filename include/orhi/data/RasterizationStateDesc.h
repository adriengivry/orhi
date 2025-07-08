/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EPolygonMode.h>
#include <orhi/types/ECullModeFlags.h>
#include <orhi/types/EFrontFace.h>

namespace orhi::data
{
	/**
	* Rasterization state descriptor
	*/
	struct RasterizationStateDesc
	{
		bool depthClampEnable = false;
		bool rasterizerDiscardEnable = false;
		types::EPolygonMode polygonMode = types::EPolygonMode::FILL;
		types::ECullModeFlags cullMode = types::ECullModeFlags::BACK_BIT;
		types::EFrontFace frontFace = types::EFrontFace::COUNTER_CLOCKWISE;
		bool depthBiasEnable = false;
		float depthBiasConstantFactor = 0.0f;
		float depthBiasClamp = 0.0f;
		float depthBiasSlopeFactor = 0.0f;
		float lineWidth = 1.0f;
	};
}
