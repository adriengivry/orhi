project "0-vulkan"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	debugdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	
	files {
		"**.h",
		"**.cpp",
	}

	includedirs {
		depsdir .. "glm/include",
		depsdir .. "glfw/include",
		"%{wks.location}../../include",
	}

	links {
		"glfw",
		"glm",
		"orhi"
    }

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
