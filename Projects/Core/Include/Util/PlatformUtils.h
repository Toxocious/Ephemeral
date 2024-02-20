#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace Ephemeral
{
    class FileDialogs
    {
    public:
        static std::string OpenFile( const char * filter );
        static std::string SaveFile( const char * filter );
    };

    class Time
    {
    public:
        static float GetTime()
        {
            return glfwGetTime();
        };
    };
}
