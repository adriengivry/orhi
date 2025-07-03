/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/api/TGraphicsPipeline.h>

namespace orhi::impl::vk
{
	struct GraphicsPipelineContext {};
	using GraphicsPipeline = api::TGraphicsPipeline<types::EGraphicsBackend::VULKAN, GraphicsPipelineContext>;
}
