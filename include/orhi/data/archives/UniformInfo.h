/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <any>
#include <string>

#include <orhi/types/EUniformType.h>

namespace orhi::data
{
	/**
	* Structure that holds information about a uniform
	*/
	struct UniformInfo
	{
		types::EUniformType type;
		std::string name;
		std::any defaultValue;
	};
}
