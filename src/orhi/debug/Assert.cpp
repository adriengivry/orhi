/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/debug/Assert.h>

#include <cassert>

void orhi::debug::Assert(bool condition, const std::string_view p_message)
{
	assert(condition && p_message.data());
}
