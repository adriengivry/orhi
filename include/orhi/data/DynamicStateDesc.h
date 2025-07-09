/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/types/EDynamicState.h>
#include <span>

namespace orhi::data
{
	/**
	* Dynamic state descriptor
	*/
	struct DynamicStateDesc
	{
		std::span<const types::EDynamicState> dynamicStates;
	};
}
