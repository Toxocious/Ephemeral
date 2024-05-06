#pragma once

#ifndef EPH_CORE_WINDOW_H
#    define EPH_CORE_WINDOW_H

#    include <Core/Ephemeral.h>

namespace Ephemeral
{
    class Window
    {
    public:
        Window( int height, int width, const char * title );
        ~Window();

        void Run();

    private:
        void CenterWindow();

        int  ShouldClose();
        void SwapBuffers();
        void PollEvents();

        GLFWwindow * GetGLFWWindow();

    private:
        std::unique_ptr<GLFWwindow, decltype( &glfwDestroyWindow )>
            m_Window;

        int          m_Height;
        int          m_Width;
        const char * m_Title;
    };
}

#endif
