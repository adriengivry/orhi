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
		"**.lua",
	}

	includedirs {
		depsdir .. "glm/include",
		depsdir .. "glfw/include",
		"%{wks.location}../../include",
	}

	links {
		"glfw",
		"glm",
		"orhi",
		"shaders"
	}

	-- Copy assets folder to output directory
	buildaction "Custom"
	buildmessage "Copying assets to output folder..."
	buildcommands {
		"{COPYDIR} %{wks.location}assets %{cfg.targetdir}/assets"
	}
	buildoutputs { "%{cfg.targetdir}/assets_copied.stamp" }

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
