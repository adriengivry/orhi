/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#include <cstdio>

#include <orhi/debug/Log.h>

namespace orhi::debug
{
	template<>
	void Log<ELogLevel::INFO>(const std::string_view p_message)
	{
		fprintf(
			stdout,
			"[INFO] %s\n",
			p_message.data()
		);
	}

	template<>
	void Log<ELogLevel::WARNING>(const std::string_view p_message)
	{
		fprintf(
			stdout,
			"[WARNING] %s\n",
			p_message.data()
		);
	}

	template<>
	void Log<ELogLevel::ERROR>(const std::string_view p_message)
	{
		fprintf(
			stderr,
			"[ERROR] %s\n",
			p_message.data()
		);
	}
}
