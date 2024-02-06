project "Editor"
    -- kind "ConsoleApp"
    kind "WindowedApp"
    language "C++"
    cppdialect "C++17"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    entrypoint "mainCRTStartup"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/" .. outputdir .. "/%{prj.name}/obj")

    files
    {
        "src/**.h",
        "src/**.cpp",
    }

    defines
    {

    }

    includedirs
    {
        "src",

        "../core/src",
        "../core/vendor",

        "%{IncludeDir.filewatch}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/examples",
		"%{IncludeDir.imguizmo}",
		"%{IncludeDir.spdlog}",
    }

    links
    {
        "core"
    }

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines { "DIST" }
        runtime "Release"
        optimize "On"
        symbols "Off"
