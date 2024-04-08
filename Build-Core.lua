project "Core"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	location "Projects/Core"

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
