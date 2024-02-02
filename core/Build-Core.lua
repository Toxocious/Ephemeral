project "core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "include.h"
	pchsource "src/include.cpp"

    files
    {
        -- Source code
        "src/include.h",
        "src/include.cpp",
        "src/Core/*.h",
        "src/Core/*.cpp",
        "src/utils/*.h",
        "src/utils/*.cpp",

        -- Vendor // GLFW
        "vendor/glfw/include/GLFW/glfw3.h",

        -- Vendor // GLM
        "vendor/glm/glm/*.hpp",
        "vendor/glm/glm/*.inl",
        "vendor/glm/glm/gtx/*.hpp",
        "vendor/glm/glm/gtx/*.inl",

        -- Vendor // Dear ImGui
        "vendor/imgui/imgui.h",
        "vendor/imgui/imgui_internal.h",
        "vendor/imgui/misc/cpp/imgui_stdlib.h",

        -- Vendor // ImGuizmo
        "vendor/imguizmo/ImGuizmo.h",
        "vendor/imguizmo/ImGuizmo.cpp",

        -- Vendor // SpdLog
        "vendor/spdlog/include/stdout_color_sinks.h",
        "vendor/spdlog/include/basic_file_sink.h",
        "vendor/spdlog/include/fmt/ostr.h",
        "vendor/spdlog/include/spdlog.h",
    }

    defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
        "IMGUI_DEFINE_MATH_OPERATORS",
	}

    includedirs
	{
		"src",

		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/glm",
		"vendor/imgui",
		"vendor/imguizmo",
	}

	links
	{
		"GLFW",
		-- "ImGui",
		"opengl32.lib",
	}

    filter "system:windows"
        systemversion "latest"
        defines { }

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
