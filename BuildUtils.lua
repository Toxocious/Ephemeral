-- Link our dependencies.
function linkDependencies()
	includedirs {
		"Libraries/glad/include",
		"Libraries/glfw/include",
		"Libraries/glm/include",
		"Libraries/imgui/include",
		"Libraries/mathgeolib/include",
		"Libraries/spdlog/include",
		"Libraries/stb_image/include",
	}

	libdirs {
		"Libraries/glad/lib",
		"Libraries/glfw/lib",
		"Libraries/glm/lib",
		"Libraries/imgui/lib",
		"Libraries/spdlog/lib",
	}

	-- Our static lib should not link against our dependencies
	filter { "kind:not StaticLib", "configurations:Debug" }
		links {
			"glad_debug",
			"glm_debug",
			"glfw3",
			"imgui",
			"spdlogd",
		}

	filter { "kind:not StaticLib", "configurations:Dist" }
		links {
			"glad_dist",
			"glm_dist",
			"glfw3",
			"imgui",
			"spdlog",
		}

	filter { "kind:not StaticLib", "configurations:Release" }
		links {
			"glad_release",
			"glm_release",
			"glfw3",
			"imgui",
			"spdlog",
		}

end

-- Include the files that we use from our dependencies.
function includeDependencies()
	includedirs {
		"Libraries/glad/include",
		"Libraries/glfw/include",
		"Libraries/glm/include",
		"Libraries/imgui/include",
		"Libraries/mathgeolib/include",
		"Libraries/spdlog/include",
		"Libraries/stb_image/include",
	}

	files {
		"Libraries/glad/include/**.h",
		"Libraries/glad/src/glad.c",

		"Libraries/glfw/include/**.h",

		"Libraries/glm/include/**.hpp",
		"Libraries/glm/include/**.inl",

		"Libraries/imgui/include/**.h",
		"Libraries/imgui/include/**.cpp",

		"Libraries/mathgeolib/include/**.h",
		"Libraries/mathgeolib/include/**.cpp",
		"Libraries/mathgeolib/include/**.inl",

		"Libraries/spdlog/include/**.h",

		"Libraries/stb_image/include/**.h",
		"Libraries/stb_image/include/**.cpp",
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
