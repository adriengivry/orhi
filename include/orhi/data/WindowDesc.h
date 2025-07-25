/**
* @project: orhi (OpenRHI)
* @author: Adrien Givry
* @licence: MIT
*/

#pragma once

#include <variant>

namespace orhi::data
{
	/**
	* @brief Win32 window descriptor for Windows platforms
	*/
	struct Win32WindowDesc 
	{ 
		void* hwnd;
	};

	/**
	* @brief X11 window descriptor for Linux platforms
	*/
	struct X11WindowDesc
	{
		void* dpy;
		uint64_t window;
	};

	/**
	* @brief Wayland window descriptor for Linux platforms
	*/
	struct WaylandWindowDesc
	{
		void* display;
		void* surface;
	};

	/**
	* @brief Metal window descriptor for apple platforms
	*/
	struct MetalWindowDesc
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
	using WindowDesc = std::variant<
		Win32WindowDesc, 
		X11WindowDesc, 
		WaylandWindowDesc, 
		MetalWindowDesc
	>;
}