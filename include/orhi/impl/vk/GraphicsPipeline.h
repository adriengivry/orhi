/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/apii/TGraphicsPipeline.h>

namespace orhi::impl::vk
{
	struct GraphicsPipelineContext {};
	using GraphicsPipeline = apii::TGraphicsPipeline<types::EGraphicsBackend::VULKAN, GraphicsPipelineContext>;
}
