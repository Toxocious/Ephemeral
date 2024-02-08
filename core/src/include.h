#pragma once

/**
 * Standard Library
 */
#include <algorithm>
#include <array>
#include <chrono>
#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef EPH_PLATFORM_WINDOWS
#    include <Windows.h>
#endif

/**
 * Vendor Dependencies
 *   - Filewatch     (https://github.com/ThomasMonkman/filewatch)
 *   - GLFW          (https://github.com/glfw/glfw)
 *   - GLAD          (https://github.com/Dav1dde/glad)
 *   - GLM           (https://github.com/g-truc/glm)
 *   - Dear ImGui    (https://github.com/ocornut/imgui)
 *   - ImGuizmos     (https://github.com/CedricGuillemet/ImGuizmo)
 *   - SpdLog        (https://github.com/gabime/spdlog)
 *   - stb_image     (https://github.com/nothings/stb)
 */
#include <GLFW/glfw3.h>

#include <glm/common.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"

#include "ImGuizmo.h"

/**
 * Ephemeral Headers
 */
#include "Constants/Editor.h"

#include "Core/Base.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "Core/Platform.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "Utils/Assert.h"
#include "Utils/Log.h"
#include "Utils/Time.h"
#include "Utils/Timer.h"
#include "Utils/Timestep.h"

// #include "Core/Log.h"
// #include "Debug/Instrumentor.h"
