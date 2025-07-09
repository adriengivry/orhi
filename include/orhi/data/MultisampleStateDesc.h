/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/ESampleCountFlags.h>

namespace orhi::data
{
	/**
	* Multisample state descriptor
	*/
	struct MultisampleStateDesc
	{
		types::ESampleCountFlags rasterizationSamples = types::ESampleCountFlags::COUNT_1_BIT;
		bool sampleShadingEnable = false;
		float minSampleShading = 1.0f;
		const uint32_t* pSampleMask = nullptr;
		bool alphaToCoverageEnable = false;
		bool alphaToOneEnable = false;
	};
}
