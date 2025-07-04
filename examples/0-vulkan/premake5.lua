project "0-vulkan"
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
		depsdir .. "glm/include",
		depsdir .. "glfw/include",
		"%{wks.location}../../include",
	}

	links {
		"glfw",
		"glm",
		"orhi"
	}

	-- Copy assets folder to output directory
	postbuildcommands {
		"{COPYDIR} %{prj.location}assets %{cfg.targetdir}/assets"
	}

	local shadersOutputDir = "%{prj.location}/assets/shaders/"
	
	-- Helper function to create shader compilation rules
	local function addShaderRule(extension, shaderType)
		filter("files:**." .. extension)
			buildmessage("Compiling " .. shaderType .. " shader %{file.name}")
			buildcommands {
				"if not exist \"" .. shadersOutputDir .. "\" mkdir \"" .. shadersOutputDir .. "\"",
				"\"%{VULKAN_SDK}\\bin\\glslangValidator.exe\" -V \"%{file.relpath}\" -o \"" .. shadersOutputDir .. "%{file.basename}." .. extension .. ".spv\""
			}
			buildoutputs { shadersOutputDir .. "%{file.basename}." .. extension .. ".spv" }
	end
	
	-- Add rules for all shader types
	addShaderRule("vert", "vertex")
	addShaderRule("frag", "fragment")
	addShaderRule("comp", "compute")
	addShaderRule("geom", "geometry")
	addShaderRule("tesc", "tessellation control")
	addShaderRule("tese", "tessellation evaluation")

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
