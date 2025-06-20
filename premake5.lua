project "orhi"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	targetdir (outputdir .. "%{cfg.buildcfg}/%{prj.name}")
	objdir (objoutdir .. "%{cfg.buildcfg}/%{prj.name}")

	print("-------------------------------------------")
	print("Generating orhi project...")

	newoption {
		trigger = "compile-opengl",
		description = "Compile OpenGL backend",
	}

	newoption {
		trigger = "compile-mock",
		description = "Compile Mock backend",
	}

	if _OPTIONS["compile-opengl"] then
		print("+ OpenGL backend selected for compilation")
		defines { "ORHI_COMPILE_OPENGL" }
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

	filter { "configurations:Debug" }
		defines { "DEBUG" }
		symbols "On"

	filter { "configurations:Release" }
		defines { "NDEBUG" }
		optimize "On"
	
	print("OpenRHI project generation complete.")
	print("-------------------------------------------")
