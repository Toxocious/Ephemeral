#pragma once

#include "include.h"

#include "Time.h"

namespace Ephemeral
{
    double Time::GetTime()
    {
        return glfwGetTime();
    }
}
