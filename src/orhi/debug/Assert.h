/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string_view>

// Enhanced assert macro with file, line, and function information
#define ORHI_ASSERT(condition, message) \
	orhi::debug::Assert(condition, message, __FILE__, __LINE__, __func__)

// Simple assert macro for backwards compatibility
#define ORHI_ASSERT_SIMPLE(condition, message) \
	orhi::debug::Assert(condition, message)

namespace orhi::debug
{
	/**
	 * @brief Enhanced assertion function with file, line, and function information
	 * @param condition The condition to check
	 * @param p_message Optional message to display on assertion failure
	 * @param p_file Source file where the assertion occurred
	 * @param p_line Line number where the assertion occurred
	 * @param p_function Function name where the assertion occurred
	 */
	void Assert(bool condition, 
				const std::string_view p_message = {},
				const char* p_file = nullptr,
				int p_line = 0,
				const char* p_function = nullptr);
}
