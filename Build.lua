include "Build-Dependencies.lua"

workspace "Ephemeral"
   architecture "x86_64"
   startproject "Editor"

   configurations {
      "Debug",
      "Release",
      "Dist"
   }

   flags
	{
		"MultiProcessorCompile"
	}

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.system}/%{cfg.architecture}/%{cfg.buildcfg}"

group "Dependencies"
	include "core/vendor/glfw"
group ""

group "Core"
	include "core/Build-Core.lua"
group ""

include "editor/Build-Editor.lua"
