project "3-texture"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")
	debugdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	
	files {
		-- Source files
		"**.h",
		"**.cpp",
		"**.lua",

		-- Shader files
		"**.vert",
		"**.frag",
		"**.comp",
		"**.geom",
		"**.tesc",
		"**.tese"
	}

	includedirs {
		depsdir .. "_glm/glm",
		depsdir .. "_glfw/glfw/include",
		depsdir .. "_stb/stb",
		"%{wks.location}../../include",
	}

	links {
		"glfw",
		"glm",
		"stb",
		"orhi"
	}

	-- Copy assets folder to output directory
	postbuildcommands {
		"{COPYDIR} %{prj.location}assets %{cfg.targetdir}/assets"
	}

	-- Add shader compilation rules
	addShaderCompilation()

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
