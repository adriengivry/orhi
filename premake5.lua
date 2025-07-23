project "orhi"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	targetdir ("bin/%{cfg.buildcfg}/%{prj.name}")
	objdir ("obj/%{cfg.buildcfg}/%{prj.name}")

	print("-------------------------------------------")
	print("Generating orhi project...")

	newoption {
		trigger = "compile-vulkan",
		description = "Compile Vulkan backend",
	}

	newoption {
		trigger = "compile-mock",
		description = "Compile Mock backend",
	}

	newoption {
		trigger = "xlib",
		description = "Use Xlib for window management (Linux only)",
	}

	newoption {
		trigger = "xcb",
		description = "Use XCB for window management (Linux only)",
	}

	newoption {
		trigger = "wayland",
		description = "Use Wayland for window management (Linux only)",
	}

	filter { "system:linux" }
		if _OPTIONS["xlib"] then
			print("+ Xlib window management selected")
			defines { "ORHI_USE_WINDOW_SYSTEM_XLIB" }
		elseif _OPTIONS["xcb"] then
			print("+ XCB window management selected")
			defines { "ORHI_USE_WINDOW_SYSTEM_XCB" }
		elseif _OPTIONS["wayland"] then
			print("+ Wayland window management selected")
			defines { "ORHI_USE_WINDOW_SYSTEM_WAYLAND" }
		end

	filter { "system:windows" }
		defines { "ORHI_USE_WINDOW_SYSTEM_WIN32" }

	filter { "system:macosx" }
		defines { "ORHI_USE_WINDOW_SYSTEM_COCOA" }
	filter {}

	if _OPTIONS["compile-vulkan"] then
		print("+ Vulkan backend selected for compilation")
		defines { "ORHI_COMPILE_VULKAN" }
		
		-- Check for Vulkan SDK
		local vulkanSDK = os.getenv("VULKAN_SDK")
		if vulkanSDK then
			print("+ Found Vulkan SDK at: " .. vulkanSDK)
		else
			error("VULKAN_SDK environment variable not set. Please install Vulkan SDK and set VULKAN_SDK environment variable.")
		end
	end

	if _OPTIONS["compile-mock"] then
		print("+ Mock backend selected for compilation")
		defines { "ORHI_COMPILE_MOCK" }
	end

	files {
		"include/**.h", -- public headers
		"src/**.h", -- private headers
		"src/**.cpp",
		"src/**.c",
	}

	includedirs {
		"include",
		"src"
	}
	
	-- Add Vulkan include directory if enabled
	filter { "options:compile-vulkan" }
		includedirs {
			"%{os.getenv('VULKAN_SDK')}/include"
		}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
	
	print("OpenRHI project generation complete.")
	print("-------------------------------------------")
