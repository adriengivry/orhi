/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <stdexcept>

namespace orhi::except
{
	class OutOfDateSwapChain : public std::runtime_error
	{
	public:
		OutOfDateSwapChain() : std::runtime_error("Swap chain out of date") {}
	};
}
