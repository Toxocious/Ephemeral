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
            "EPH_ENABLE_ASSERTS",
            "GLEW_STATIC",
            "SPDLOG_COMPILED_LIB",
            "_CRT_SECURE_NO_WARNINGS",
        }
        runtime "Debug"
        optimize "Off"
		symbols "On"

	filter { "configurations:Release" }
        defines {
            "EPH_RELEASE",
            "EPH_ENABLE_ASSERTS",
            "GLEW_STATIC",
            "SPDLOG_COMPILED_LIB",
            "_CRT_SECURE_NO_WARNINGS",
        }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter { "configurations:Dist" }
        defines {
            "EPH_DIST",
            "EPH_ENABLE_ASSERTS",
            "GLEW_STATIC",
            "SPDLOG_COMPILED_LIB",
            "_CRT_SECURE_NO_WARNINGS",
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
