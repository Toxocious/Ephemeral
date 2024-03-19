#include <Core/Ephemeral.h>

#include <Platforms/OpenGL/OpenGLContext.h>

#include <Util/Profile.h>

#include <glad/glad.h>

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

        int status = gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );
        EPH_CORE_ASSERT( status, "Failed to initialize Glad!" );

        EPH_CORE_INFO( "OpenGL Info:" );
        EPH_CORE_INFO( "  Version: {0}.{1}", GLVersion.major, GLVersion.minor );

        EPH_CORE_ASSERT( GLVersion.major > 4 || ( GLVersion.major == 4 && GLVersion.minor >= 5 ), "Ephemeral requires at least OpenGL version 4.5!" );
    }

    void OpenGLContext::SwapBuffers()
    {
        EPH_PROFILE_FUNCTION();

        glfwSwapBuffers( m_WindowHandle );
    }
}
