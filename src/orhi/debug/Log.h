/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <string_view>

#define ORHI_LOG_INFO(message) orhi::debug::Log<orhi::debug::ELogLevel::INFO>(message)
#define ORHI_LOG_WARNING(message) orhi::debug::Log<orhi::debug::ELogLevel::WARNING>(message)
#define ORHI_LOG_ERROR(message) orhi::debug::Log<orhi::debug::ELogLevel::ERROR>(message)

namespace orhi::debug
{
	enum class ELogLevel
	{
		INFO,
		WARNING,
		ERROR
	};

	template<ELogLevel Level>
	void Log(const std::string_view p_message);
}
