/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ECullModeFlags.h>
#include <orhi/types/EFrontFace.h>
#include <orhi/types/EPolygonMode.h>

namespace orhi::data
{
	/**
	* @brief Rasterization state descriptor for graphics pipelines
	* 
	* Defines the rasterization configuration including polygon mode (fill, line, point),
	* face culling, front face orientation, depth bias, and line width. Controls how
	* primitives are converted to fragments during the rasterization stage.
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
