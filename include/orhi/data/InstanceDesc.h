/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <any>
#include <cstdint>
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
		void* win32_windowHandle; // is the Win32 HWND for the window to associate the surface with.
		void* win32_instanceHandle; // is the Win32 HINSTANCE for the window to associate the surface with.
		void* xlib_display; // is the Xlib Display for the window to associate the surface with.
		std::any xlib_window; // is the Xlib Window for the window to associate the
	};
}
