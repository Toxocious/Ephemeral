#pragma once

#include <filesystem>
#include <iostream>
#include <memory>

#if defined _WIN32
#    include <Windows.h>
#endif

#ifndef EPH_IMPL_IMGUI
#    define EPH_IMPL_IMGUI

#    ifndef IMGUI_IMPL_OPENGL_LOADER_GLAD
#        define IMGUI_IMPL_OPENGL_LOADER_GLAD
#    endif

#    ifndef IMGUI_INCLUDE_IMCONFIG_H
#        define IMGUI_INCLUDE_IMCONFIG_H
#    endif

#    include <imgui.h>
#endif

#ifndef EPH_IMPL_GLAD
#    define EPH_IMPL_GLAD
#    include <glad/glad.h>
#endif

#ifndef EPH_IMPL_GLFW
#    define EPH_IMPL_GLFW
#    include <glfw/glfw3.h>

#    include <gl/GL.h>
#endif

#ifndef EPH_IMPL_GLM
#    define EPH_IMPL_GLM
#    define GLM_FORCE_CXX17
#    define GLM_EXTERNAL_TEMPLATE

#    include <glm/glm.hpp>
#    include <glm/gtc/matrix_transform.hpp>
#    include <glm/gtc/type_ptr.hpp>
#    include <glm/vec2.hpp>
#    include <glm/vec4.hpp>
#endif

#ifndef EPH_IMPL_SPDLOG
#    define EPH_IMPL_SPDLOG
#    pragma warning( push, 0 )
#    ifdef EPH_DEBUG
#        pragma comment( lib, "spdlogd" )
#    else
#        pragma comment( lib, "spdlog" )
#    endif
#    include <spdlog/spdlog.h>

#    include <spdlog/fmt/ostr.h>

#    include <spdlog/sinks/basic_file_sink.h>
#    include <spdlog/sinks/stdout_color_sinks.h>
#    pragma warning( pop )
#endif

#ifndef EPH_CORE_HEADERS
#    define EPH_CORE_HEADERS
#    include <Core/Global.h>

#    include <Util/Assert.h>
#    include <Util/Log.h>
#    include <Util/Macro.h>
#endif
