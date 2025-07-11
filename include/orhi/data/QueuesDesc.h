/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <vector>

namespace orhi::data
{
	/**
	* @brief Descriptor for queue family indices used in device creation
	* 
	* Contains the indices of queue families that will be used by a logical device.
	* Queue families define the types of operations (graphics, compute, transfer)
	* that queues can perform.
	*/
	struct QueuesDesc
	{
		std::vector<uint32_t> indices;
	};
}
