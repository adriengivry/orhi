workspace "orhi-examples"
	configurations { "Debug", "Release" }
	platforms { "x64" }
	startproject "1-triangle"

	newoption {
		trigger = "gfxapi",
		value = "API",
		description = "Define the graphics API to use (e.g., DX12, Vulkan, Mock)",
		allowed = {
			{ "dx12", "Use DirectX12 as the graphics API" },
			{ "vulkan", "Use Vulkan as the graphics API" },
			{ "mock", "Use Mock as the graphics API" }
		},
		default = "vulkan"
	}

	-- Get Vulkan SDK path for shader compilation
	vulkanSDK = os.getenv("VULKAN_SDK")
	if not vulkanSDK then
		print("WARNING: VULKAN_SDK environment variable not set. Shader compilation may fail.")
		vulkanSDK = ""
	else
		print("Found Vulkan SDK at: " .. vulkanSDK)
	end

	filter { "options:gfxapi=vulkan" }
		defines { "ORHI_SELECT_VULKAN" }

	filter { "options:gfxapi=dx12" }
		defines { "ORHI_SELECT_DX12" }

	filter { "options:gfxapi=mock" }
		defines { "ORHI_SELECT_MOCK" }

outputdir = "%{wks.location}/../bin/"
objoutdir = "%{wks.location}/../obj/"
depsdir = "%{wks.location}/deps/"

-- Global shader compilation function
function addShaderCompilation()
	local shadersOutputDir = "%{prj.location}/assets/shaders/"
	
	-- Helper function to create shader compilation rules
	local function addShaderRule(extension, shaderType)
		filter("files:**." .. extension)
			buildmessage("Compiling " .. shaderType .. " shader %{file.name}")
			buildcommands {
				"if not exist \"" .. shadersOutputDir .. "\" mkdir \"" .. shadersOutputDir .. "\"",
				"\"" .. vulkanSDK .. "\\bin\\glslangValidator.exe\" -V \"%{file.relpath}\" -o \"" .. shadersOutputDir .. "%{file.basename}." .. extension .. ".spv\""
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
	
	filter {} -- Reset filter
end

group "examples"
	include "1-triangle"
	include "2-cube"
	include "3-texture"
	include "4-depth"
	include "5-mipmaps"
	include "6-msaa"
	include "7-particles"
	include "8-push-constants"
group ""

group "examples/deps"
	include "deps/_glm"
	include "deps/_glfw"
	include "deps/_stb"
group ""

include "../"
