/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <variant>

namespace orhi::data
{
	// Expects "ORHI_USE_WINDOW_SYSTEM_WIN32" platform macro
	struct WindowsWindow 
	{ 
		void* hwnd;
	};

	// Expects "ORHI_USE_WINDOW_SYSTEM_XLIB" or "ORHI_USE_WINDOW_SYSTEM_XCB"
	struct X11Window
	{
		void* dpy;
		uint64_t window;
	};

	// Expects "ORHI_USE_WINDOW_SYSTEM_WAYLAND"
	struct WaylandWindow
	{
		void* display;
		void* surface;
	};

	// Expects "ORHI_USE_WINDOW_SYSTEM_COCOA"
	struct MetalWindow
	{
		void* caMetalLayer;
	};

	/**
	* @brief Variant type for platform-specific window representations
	* 
	* This variant type can hold any of the platform-specific window structures,
	* allowing for a unified interface when working with windows across different
	* platforms.
	*/
	using Window = std::variant<
		WindowsWindow, 
		X11Window, 
		WaylandWindow, 
		MetalWindow
	>;
}