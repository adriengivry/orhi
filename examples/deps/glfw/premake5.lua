project "glfw"
	kind "StaticLib"
	language "C"
	cdialect "C17"
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	warnings "Off"

	files {
		"**.h",
		"**.c",
		"**.m",
		"**.lua"
	}

	includedirs {
		"include"
	}

	filter { "system:windows" }
		defines { "_GLFW_WIN32" }

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
