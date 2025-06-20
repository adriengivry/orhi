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
	* Structure that holds the result of a shader compilation
	*/
	struct ShaderCompilationResult
	{
		bool success;
		std::string message;
	};
}
