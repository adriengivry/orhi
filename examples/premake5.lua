workspace "orhi-examples"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	startproject "1-triangle"

	newoption {
		trigger = "gfxapi",
		value = "API",
		description = "Define the graphics API to use (e.g., OpenGL, Vulkan, Mock)",
		allowed = {
			{ "opengl", "Use OpenGL as the graphics API" },
			{ "vulkan", "Use Vulkan as the graphics API" },
			{ "mock", "Use Mock as the graphics API" }
		},
		default = "opengl"
	}

	filter { "options:gfxapi=opengl" }
		defines { "ORHI_SELECT_OPENGL" }

	filter { "options:gfxapi=vulkan" }
		defines { "ORHI_SELECT_VULKAN" }

	filter { "options:gfxapi=mock" }
		defines { "ORHI_SELECT_MOCK" }

	VULKAN_SDK = os.getenv("VK_SDK_PATH")

	-- Check if VULKAN_SDK is set to a valid path
	if not VULKAN_SDK or VULKAN_SDK == "" then
		error("Couldn't find Vulkan SDK. Please make sure the Vulkan SDK is installed and the VK_SDK_PATH environment variable is set.")
	end
	
	print("Vulkan SDK Path: " .. VULKAN_SDK)


outputdir = "%{wks.location}/../bin/"
objoutdir = "%{wks.location}/../bin-int/"
depsdir = "%{wks.location}/deps/"

group "examples"
	include "1-triangle"
	include "2-cube"
	include "3-framebuffer"
	include "4-geometry"
	include "5-compute"
	include "6-tessellation"
group ""

group "examples/deps"
	include "deps/glm"
	include "deps/glfw"
group ""

include "../"
