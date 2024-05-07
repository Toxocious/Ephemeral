#pragma once

#ifndef EPH_CORE_WINDOW_H
#    define EPH_CORE_WINDOW_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

namespace Ephemeral
{
    class Window : public Module
    {
    public:
        Window( bool enabled = true );
        ~Window();

    public:
        bool Initialize( const int height, const int width, const char * title ) override;
        bool Start() override;
        bool CleanUp() override;

        UpdateStatus PreUpdate() override;
        UpdateStatus Update() override;
        UpdateStatus PostUpdate() override;

        int GetWidth() const;
        int GetHeight() const;

        void SetWindowSize( const int & height, const int & width );
        void UpdateWindowSize();

        void CenterWindow();

    private:
        GLFWwindow * GetGLFWWindow();

        int  ShouldClose();
        void SwapBuffers();
        void PollEvents();

    private:
        std::unique_ptr<GLFWwindow, decltype( &glfwDestroyWindow )> m_Window;

        int          m_Height;
        int          m_Width;
        const char * m_Title;
    };
}

#endif
