project "spdlog"
    kind "StaticLib"
    language "C"
    staticruntime "off"

    targetdir ("Build/" .. outputdir .. "/%{prj.name}")
    objdir ("Build/" .. outputdir .. "/%{prj.name}/Artifacts")

    files
    {
        "include/spdlog/spdlog.h",
        "include/spdlog/*.h",
    }

    includedirs
    {
        "include",
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
