project "Glew"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir ("Build/" .. outputdir .. "/%{prj.name}")
    objdir ("Build/" .. outputdir .. "/%{prj.name}/Artifacts")

    files
    {
        "include/GL/glew.h",
        "include/GL/*.h",

        "src/visualinfo.c",
    }

    includedirs
    {
        "include",
        "src",
    }

    defines
	{
        "GLEW_STATIC",
	}

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
