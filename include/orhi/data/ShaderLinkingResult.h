/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string>

namespace orhi::data
{
	/**
	* Structure that contains the result of a shader linking operation
	*/
	struct ShaderLinkingResult
	{
		const bool success;
		const std::string message;
	};
}
