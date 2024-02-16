project "Editor"
	-- kind "ConsoleApp"
    kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

    entrypoint "mainCRTStartup"

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
