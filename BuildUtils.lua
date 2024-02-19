-- Link our dependencies.
function linkDependencies()
	includedirs {
		"Libraries/glew/include",
		"Libraries/glfw/include",
		"Libraries/imgui/include",
		"Libraries/spdlog/include",
	}

	libdirs {
		"Libraries/glew/lib",
		"Libraries/glfw/lib",
		"Libraries/imgui/lib",
	}

	-- Our static lib should not link against our dependencies
	filter "kind:not StaticLib"
		links {
			"glew32",
			"glfw3",
			"imgui",
		}
end

-- Include the files that we use from our dependencies.
function includeDependencies()
	includedirs {
		"Libraries/glfw/include",
		"Libraries/glew/include",
		"Libraries/imgui/include",
		"Libraries/spdlog/include",
	}

	files {
		"Libraries/glew/include/**.h",
		"Libraries/glfw/include/**.h",
		"Libraries/imgui/include/**.h",
		"Libraries/imgui/include/**.cpp",
		"Libraries/spdlog/include/**.h",
	}

	removefiles {
		"Libraries/imgui/include/examples/imgui_impl_vulkan.h",
		"Libraries/imgui/include/examples/imgui_impl_vulkan.cpp",
	}
end

-- Include the Projects/Core code
function useCoreLib()
	-- The library's public headers
	includedirs
	{
		"Projects/Core/**"
	}

	-- We link against a library that's in the same workspace, so we can just use the project name - premake is really smart and will handle everything for us.
	links "Core"

	-- Users of Core need to link GLFW and ImGui
	linkDependencies()
end
