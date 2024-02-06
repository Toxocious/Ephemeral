#pragma once

#include "include.h"

#include <memory>
#include <string>

// Forward declare GLFWwindow to avoid including glfw3.h
struct GLFWwindow;

namespace Ephemeral
{
    class Window
    {
    public:
        Window( int width, int height, const std::string & title );
        ~Window();

        bool shouldClose() const noexcept;

        void pollEvents() const noexcept;

        void swapBuffers() const noexcept;

        std::pair<int, int> getWindowSize() const noexcept;

    private:
        GLFWwindow * wnd;
    };
}
