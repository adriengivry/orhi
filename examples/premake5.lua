workspace "orhi-examples"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	startproject "0-vulkan"

	newoption {
		trigger = "gfxapi",
		value = "API",
		description = "Define the graphics API to use (e.g., Vulkan, Mock)",
		allowed = {
			{ "vulkan", "Use Vulkan as the graphics API" },
			{ "mock", "Use Mock as the graphics API" }
		},
		default = "opengl"
	}

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
objoutdir = "%{wks.location}/../obj/"
depsdir = "%{wks.location}/deps/"

group "examples"
	include "0-vulkan"
group ""

group "examples/deps"
	include "deps/_glm"
	include "deps/_glfw"
group ""

include "../"
