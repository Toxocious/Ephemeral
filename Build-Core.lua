project "Core"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"

	files
	{
		"Projects/Core/Include/**/*.h",
		"Projects/Core/Include/**/*.hpp",
		"Projects/Core/Source/**/*.c",
		"Projects/Core/Source/**/*.cpp",
	}

	includedirs
    {
        "Projects/Core/Include",
        "Projects/Core/Source",
    }

	includeDependencies()
