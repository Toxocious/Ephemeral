#include <Platforms/OpenGL/OpenGLContext.h>

#include <Util/Profile.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Ephemeral
{
    OpenGLContext::OpenGLContext( GLFWwindow * windowHandle )
        : m_WindowHandle( windowHandle )
    {
        EPH_CORE_ASSERT( windowHandle, "Window handle is null!" )
    }

    void OpenGLContext::Init()
    {
        EPH_PROFILE_FUNCTION();

        glfwMakeContextCurrent( m_WindowHandle );

        // Initialize Glew
        GLenum err = glewInit();
    }

    void OpenGLContext::SwapBuffers()
    {
        EPH_PROFILE_FUNCTION();

        glfwSwapBuffers( m_WindowHandle );
    }
}
