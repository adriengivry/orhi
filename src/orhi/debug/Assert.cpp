/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <orhi/debug/Assert.h>
#include <orhi/debug/Log.h>

#include <cassert>
#include <cstdlib>
#include <string>
#include <sstream>

namespace orhi::debug
{
	void Assert(bool condition, 
				const std::string_view p_message,
				const char* p_file,
				int p_line,
				const char* p_function)
	{
		if (!condition)
		{
			// Build detailed assertion message
			std::ostringstream assertMessage;
			assertMessage << "ASSERTION FAILED";
			
			if (p_file && p_line > 0)
			{
				// Extract just the filename from the full path
				const char* filename = p_file;
				const char* lastSlash = p_file;
				while (*lastSlash)
				{
					if (*lastSlash == '/' || *lastSlash == '\\')
						filename = lastSlash + 1;
					lastSlash++;
				}
				
				assertMessage << " in " << filename << ":" << p_line;
			}
			
			if (p_function)
			{
				assertMessage << " in function '" << p_function << "'";
			}
			
			if (!p_message.empty())
			{
				assertMessage << " - " << p_message;
			}
			
			// Log the assertion failure
			Log<ELogLevel::ERROR>(assertMessage.str());
			
			// In debug builds, use assert for potential debugger break
			// In release builds, abort directly
			#ifdef NDEBUG
				std::abort();
			#else
				assert(false && "ORHI assertion failed - check log for details");
			#endif
		}
	}
}
