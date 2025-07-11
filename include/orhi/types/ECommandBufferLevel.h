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
	* @brief Command buffer level enumeration
	* 
	* Defines the hierarchy level of command buffers. Primary command buffers
	* can be submitted directly to queues, while secondary command buffers
	* must be executed from within primary command buffers.
	*/
	enum class ECommandBufferLevel
	{
		PRIMARY = 0,
		SECONDARY = 1,
	};
}
