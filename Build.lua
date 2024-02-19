include "./BuildUtils.lua"

workspace "Ephemeral"
    language "C++"
    architecture "x86_64"
    location "Generated"
    startproject "Editor"

    flags
    {
        "MultiProcessorCompile"
    }

	configurations { "Debug", "Release", "Dist" }

	filter { "configurations:Debug" }
        defines {
            "EPH_DEBUG",
            "GLEW_STATIC",
            "EPH_ENABLE_ASSERTS"
        }
        runtime "Debug"
        optimize "Off"
		symbols "On"

	filter { "configurations:Release" }
        defines {
            "EPH_RELEASE",
            "GLEW_STATIC",
            "EPH_ENABLE_ASSERTS"
        }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter { "configurations:Dist" }
        defines {
            "EPH_DIST",
            "GLEW_STATIC",
            "EPH_ENABLE_ASSERTS"
        }
        runtime "Release"
        optimize "On"
        symbols "Off"

	filter { }

	targetdir ("Build/Binaries/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Artifacts/%{prj.name}/%{cfg.longname}")

    -- Our project-specific premake configurations
    include "Build-Core.lua"
    include "Build-Editor.lua"
