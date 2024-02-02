#pragma once

#include "include.h"

#include "Time.h"

namespace Ephemeral
{
    float Time::GetTime()
    {
        return glfwGetTime();
    }
}
