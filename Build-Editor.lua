project "Editor"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"
    location "Projects/Editor"

    entrypoint "mainCRTStartup"

    targetname "Ephemeral Editor"

    files
    {
        "Projects/Editor/**/*.h",
        "Projects/Editor/**/*.c",
        "Projects/Editor/**/*.hpp",
        "Projects/Editor/**/*.cpp",
    }

	includedirs
    {
        "Projects/Core/Include"
    }

	useCoreLib()

	filter { "system:windows" }
		links
        {
            "OpenGL32"
        }

	filter { "system:not windows" }
		links
        {
            "GL"
        }

    filter { "configurations:Debug" }
        kind "ConsoleApp"

	filter { "configurations:Release" }
        kind "WindowedApp"

    filter { "configurations:Dist" }
        kind "WindowedApp"
