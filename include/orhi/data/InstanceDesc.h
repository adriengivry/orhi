/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <orhi/data/Window.h>

#include <string>
#include <vector>

namespace orhi::data
{
	/**
	* @brief Descriptor for graphics instance creation
	* 
	* Contains the configuration for creating a graphics API instance, including
	* debug settings, required extensions, and platform-specific window handles
	* for surface creation and presentation.
	*/
	struct InstanceDesc
	{
		bool debug;
		std::vector<std::string> extensions;
		Window window;
	};
}
