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
	* @brief Dynamic state descriptor for graphics pipelines
	* 
	* Specifies which pipeline states can be changed dynamically at command
	* buffer recording time without requiring a new pipeline object. Dynamic
	* states provide flexibility for frequently changing rendering parameters.
	*/
	struct DynamicStateDesc
	{
		std::span<const types::EDynamicState> dynamicStates;
	};
}
