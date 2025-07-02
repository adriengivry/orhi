/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <orhi/types/EFormat.h>

namespace orhi::data
{
	/**
	* Struct containing the optiomal swap chain description for the current context
	*/
	struct SwapChainDesc
	{
		types::EFormat format;
	};
}
