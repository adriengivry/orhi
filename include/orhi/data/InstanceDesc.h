/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace orhi::data
{
	/**
	* Struct containing information about the instance
	*/
	struct InstanceDesc
	{
		bool debug;
		std::vector<std::string> extensions;
		void* win32_windowHandle; // is the Win32 HWND for the window to associate the surface with.
		void* win32_instanceHandle; // is the Win32 HINSTANCE for the window to associate the surface with.
	};
}
