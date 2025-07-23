/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <variant>

namespace orhi::data
{
	// Expects "WIN32" platform macro
	struct WindowsWindow 
	{ 
		void* hwnd;             //    HWND
	};

	// Expects "ORHI_ENABLE_XLIB_SUPPORT" or "ORHI_ENABLE_XCB_SUPPORT"
	struct X11Window
	{      
		void* dpy;              //    Display
		uint64_t window;        //    Window
	};

	// Expects "ORHI_ENABLE_WAYLAND_SUPPORT"
	struct WaylandWindow
	{
		void* display;          //    wl_display
		void* surface;          //    wl_surface
	};

	// Expects "APPLE" platform macro
	struct MetalWindow
	{
		void* caMetalLayer;     //    CAMetalLayer
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