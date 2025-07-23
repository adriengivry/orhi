project "glfw"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	warnings "Off"

	files {
		"glfw/include/**.h",
		"glfw/src/**.c",
		"glfw/src/**.h",
		"premake5.lua"
	}

	includedirs {
		"include"
	}

    filter { "system:windows" }
    	defines { "_GLFW_WIN32" }

	filter { "system:linux" }
		defines { "_GLFW_X11", "_GNU_SOURCE" }
		removefiles {
			"glfw/src/win32_*",
			"glfw/src/cocoa_*",
			"glfw/src/posix_time.h",
			"glfw/src/wgl_*"
		}

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
