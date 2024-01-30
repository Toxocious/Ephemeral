project "Core"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"
    staticruntime "off"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",

        "vendor/glm/glm/**.hpp",
        "vendor/glm/glm/**.inl",
        "vendor/imguizmo/ImGuizmo.h",
        "vendor/imguizmo/ImGuizmo.cpp"
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
		-- "GLFW",
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
