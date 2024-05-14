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

    filter { "system:windows" }
		systemversion "latest"
        files { 'Projects/Core/Assets/Resources.rc', '**.ico' }
        vpaths { [ 'Projects/Core/Assets/*' ] = { '**.ico' } }

	filter { "configurations:Debug" }
        defines {
            "EPH_DEBUG",
            "EPH_ENABLE_ASSERTS",
            "EPH_PLATFORM_WINDOWS",
            "DSPDLOG_COMPILED_LIB",
            "_CRT_SECURE_NO_WARNINGS",
        }
        runtime "Debug"
        optimize "Debug"
		symbols "Full"

	filter { "configurations:Release" }
        defines {
            "EPH_RELEASE",
            "EPH_ENABLE_ASSERTS",
            "EPH_PLATFORM_WINDOWS",
            "SPDLOG_COMPILED_LIB",
            "_CRT_SECURE_NO_WARNINGS",
        }
        runtime "Release"
        optimize "Off"
        -- optimize "On"
        -- symbols "On"

    filter { "configurations:Dist" }
        defines {
            "EPH_DIST",
            "EPH_ENABLE_ASSERTS",
            "EPH_PLATFORM_WINDOWS",
            "SPDLOG_COMPILED_LIB",
            "_CRT_SECURE_NO_WARNINGS",
        }
        runtime "Release"
        optimize "Off"
        -- optimize "On"
        -- symbols "Off"

    filter {}

	targetdir ("Build/Binaries/%{prj.name}/%{cfg.longname}")
	objdir ("Build/Artifacts/%{prj.name}/%{cfg.longname}")

    -- Our project-specific premake configurations
    include "Build-Core.lua"
    include "Build-Editor.lua"
