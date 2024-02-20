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
        

        // int status = gladLoadGLLoader( ( GLADloadproc ) glfwGetProcAddress );
        // EPH_CORE_ASSERT( status, "Failed to initialize Glad!" );

        // EPH_CORE_INFO( "OpenGL Info:" );
        // EPH_CORE_INFO( "  Vendor: {0}", glGetString( GL_VENDOR ) );
        // EPH_CORE_INFO( "  Renderer: {0}", glGetString( GL_RENDERER ) );
        // EPH_CORE_INFO( "  Version: {0}", glGetString( GL_VERSION ) );
    }

    void OpenGLContext::SwapBuffers()
    {
        EPH_PROFILE_FUNCTION();

        glfwSwapBuffers( m_WindowHandle );
    }
}
