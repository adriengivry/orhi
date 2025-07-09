/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/data/Extent3D.h>
#include <orhi/types/EFormat.h>
#include <orhi/types/ETextureUsageType.h>
#include <orhi/types/ETextureType.h>
#include <orhi/types/ETextureTiling.h>
#include <orhi/types/ETextureLayout.h>
#include <orhi/types/ESampleCountFlags.h>
#include <orhi/types/EGraphicsBackend.h>
#include <orhi/api/TTexture.h>

namespace orhi::data
{
	/**
	*
	*/
	struct SamplerDesc
	{
		// Mag filter
		// Min filter
		// addressModeU
		// addressModeV
		// addressModeW
		bool anisotropy = false;
		bool unnormalizedCoordinates = false;
		bool compareEnable = false;
		// compare op
		// mipmap mode
		float mipLodBias = 0.0f;
		float minLod = 0.0f;
		float maxLod = 0.0f;
	};
}
