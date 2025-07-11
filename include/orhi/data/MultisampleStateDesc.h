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
	* @brief Multisample state descriptor for graphics pipelines
	* 
	* Defines the multisampling configuration for anti-aliasing, including
	* sample count, sample shading, and alpha-to-coverage operations.
	* Used to improve rendering quality by reducing aliasing artifacts.
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
