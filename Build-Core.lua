project "Core"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	staticruntime "off"

	location "Projects/Core"

	pchheader "Core/Ephemeral.h"
	pchsource "Projects/Core/Source/Core/Ephemeral.cpp"

	files
	{
		"Projects/Core/Assets/**/*.frag",
		"Projects/Core/Assets/**/*.vert",
		"Projects/Core/Include/**/*.h",
		"Projects/Core/Include/**/*.hpp",
		"Projects/Core/Source/**/*.c",
		"Projects/Core/Source/**/*.cpp",
	}

	includedirs
    {
		"Projects/Core/Assets",
        "Projects/Core/Include",
        "Projects/Core/Source",
    }

	includeDependencies()

	filter { 'files:Libraries/**.c' }
   		flags { 'NoPCH' }

	filter { 'files:Libraries/**.cpp' }
   		flags { 'NoPCH' }
