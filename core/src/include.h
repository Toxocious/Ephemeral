#pragma once

// -- Standard Library
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

// -- Vendor Dependencies
//   ---- GLFW
#include <GLFW/glfw3.h>

//   ---- GLM
#include <glm/common.hpp>

//   ---- Dear ImGui
#include "imgui.h"
#include "imgui_internal.h"

#include "ImGuizmo.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

// -- Ephemeral
#include "Core/Base.h"
#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"
#include "Core/Platform.h"

// #include "Core/Log.h"

// #include "Debug/Instrumentor.h"
