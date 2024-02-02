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

         -- Vendor // Filewatch
        "vendor/filewatch/FileWatch.h",

        -- Vendor // GLFW
        "vendor/glfw/include/GLFW/glfw3.h",

        -- Vendor // Glad
        "vendor/glad/include/glad/glad.h",
        "vendor/glad/include/KHR/khrplatform.h",
        "vendor/glad/src/glad.c",

        -- Vendor // GLM
        "vendor/glm/glm/common.hpp",
        "vendor/glm/glm/**/*.hpp",
        "vendor/glm/glm/**/*.inl",

        -- Vendor // Dear ImGui
        "vendor/imgui/imgui.h",
        "vendor/imgui/imgui_internal.h",
        "vendor/imgui/examples/imgui_impl_glfw.h",
        "vendor/imgui/examples/imgui_impl_opengl3.h",
        "vendor/imgui/examples/imgui_impl_vulkan.h",
        "vendor/imgui/examples/imgui_impl_win32.h",
        "vendor/imgui/misc/cpp/imgui_stdlib.h",

        -- Vendor // ImGuizmo
        "vendor/imguizmo/ImGuizmo.h",
        "vendor/imguizmo/ImGuizmo.cpp",

        -- Vendor // SpdLog
        "vendor/spdlog/include/stdout_color_sinks.h",
        "vendor/spdlog/include/basic_file_sink.h",
        "vendor/spdlog/include/fmt/ostr.h",
        "vendor/spdlog/include/spdlog.h",

        -- Vendor // stb_image
        "vendor/stb_image/*.h",
        "vendor/stb_image/*.cpp",
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

		"%{IncludeDir.filewatch}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.ImGui}/examples",
		"%{IncludeDir.imguizmo}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.spdlog}",
	}

	links
	{
		"GLFW",
        "Glad",
		"ImGui",

		"opengl32.lib",
	}

    filter "files:vendor/glad/src/**.c"
	    flags { "NoPCH" }

    filter "files:vendor/stb_image/**.cpp"
	    flags { "NoPCH" }

    filter "files:vendor/ImGuizmo/**.cpp"
	    flags { "NoPCH" }

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
