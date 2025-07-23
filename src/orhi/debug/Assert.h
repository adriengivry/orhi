/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string>

#define ORHI_ASSERT(condition, message) orhi::debug::Assert(condition, message)

namespace orhi::debug
{
	void Assert(bool condition, const std::string_view p_message = {});
}
