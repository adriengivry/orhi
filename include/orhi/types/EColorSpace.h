/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>

namespace orhi::types
{
	/**
	* @brief Color space enumeration for surface presentation
	* 
	* Defines the color space interpretation for swap chain surfaces,
	* including standard RGB, wide gamut, and HDR color spaces.
	* Affects how colors are interpreted and displayed on the output device.
	*/
	enum class EColorSpace
	{
		SRGB_NONLINEAR_KHR = 0,
		DISPLAY_P3_NONLINEAR_EXT = 1000104001,
		EXTENDED_SRGB_LINEAR_EXT = 1000104002,
		DISPLAY_P3_LINEAR_EXT = 1000104003,
		DCI_P3_NONLINEAR_EXT = 1000104004,
		BT709_LINEAR_EXT = 1000104005,
		BT709_NONLINEAR_EXT = 1000104006,
		BT2020_LINEAR_EXT = 1000104007,
		HDR10_ST2084_EXT = 1000104008,
		DOLBYVISION_EXT = 1000104009,
		HDR10_HLG_EXT = 1000104010,
		ADOBERGB_LINEAR_EXT = 1000104011,
		ADOBERGB_NONLINEAR_EXT = 1000104012,
		PASS_THROUGH_EXT = 1000104013,
		EXTENDED_SRGB_NONLINEAR_EXT = 1000104014,
		DISPLAY_NATIVE_AMD = 1000213000,
		DCI_P3_LINEAR_EXT = DISPLAY_P3_LINEAR_EXT,
	};
}
