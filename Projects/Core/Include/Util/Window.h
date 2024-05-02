#pragma once

#ifndef EPH_CORE_WINDOW_H
#    define EPH_CORE_WINDOW_H

#    include <Core/Ephemeral.h>
#    include <Renderer/Shader.h>

namespace Ephemeral
{
    class Window
    {
    public:
        Window( int height, int width, const char * title );
        ~Window();

        void Run();

    private:
        void CompileShaders();

        int  ShouldClose();
        void SwapBuffers();
        void PollEvents();

        GLFWwindow * GetGLFWWindow();

    private:
        std::unique_ptr<GLFWwindow, decltype( &glfwDestroyWindow )>
            m_Window;

        Ephemeral::Shader m_ShaderProgram;

        GLuint VBO, VAO, EBO;

        int          m_Height;
        int          m_Width;
        const char * m_Title;
    };
}

#endif