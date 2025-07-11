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
	* @brief Presentation mode enumeration for swap chain display
	* 
	* Defines how rendered images are presented to the display surface,
	* controlling synchronization, frame rate, and buffering behavior.
	* Affects visual quality, latency, and power consumption.
	*/
	enum class EPresentMode
	{
		IMMEDIATE_KHR = 0,
		MAILBOX_KHR = 1,
		FIFO_KHR = 2,
		FIFO_RELAXED_KHR = 3,
		SHARED_DEMAND_REFRESH_KHR = 1000111000,
		SHARED_CONTINUOUS_REFRESH_KHR = 1000111001,
		FIFO_LATEST_READY_EXT = 1000361000,
	};
}
