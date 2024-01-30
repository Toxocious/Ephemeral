#pragma once

#include "time.h"

#include <chrono>

#include <GLFW/glfw3.h>

namespace Ephemeral
{
    float Time::GetTime()
    {
        return glfwGetTime();
    }
}
