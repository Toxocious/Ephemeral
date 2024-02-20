#include <Platforms/OpenGL/OpenGLRenderAPI.h>

#include <Util/Profile.h>

// #include <glad/glad.h>

#ifndef GLEW_STATIC
#    define GLEW_STATIC
#endif

#ifndef GL_SILENCE_DEPRECATION
#    define GL_SILENCE_DEPRECATION
#endif

#include <Core/Ephemeral.h>

// Library headers
#pragma comment( lib, "glew32s" )
#include <GL/glew.h>

namespace Ephemeral
{
    void OpenGLMessageCallback(
        unsigned     source,
        unsigned     type,
        unsigned     id,
        unsigned     severity,
        int          length,
        const char * message,
        const void * userParam
    )
    {
        switch ( severity )
        {
            case GL_DEBUG_SEVERITY_HIGH:
                EPH_CORE_CRITICAL( message );
                return;
            case GL_DEBUG_SEVERITY_MEDIUM:
                EPH_CORE_ERROR( message );
                return;
            case GL_DEBUG_SEVERITY_LOW:
                EPH_CORE_WARN( message );
                return;
            case GL_DEBUG_SEVERITY_NOTIFICATION:
                EPH_CORE_TRACE( message );
                return;
        }

        EPH_CORE_ASSERT( false, "Unknown severity level!" );
    }

    void OpenGLRendererAPI::Init()
    {
        EPH_PROFILE_FUNCTION();

#ifdef EPH_DEBUG
        glEnable( GL_DEBUG_OUTPUT );
        glEnable( GL_DEBUG_OUTPUT_SYNCHRONOUS );
        glDebugMessageCallback( OpenGLMessageCallback, nullptr );

        glDebugMessageControl( GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE );
#endif

        // glEnable( GL_BLEND );
        // glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        // glEnable( GL_DEPTH_TEST );
        // glEnable( GL_LINE_SMOOTH );
    }

    void OpenGLRendererAPI::SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
    {
        glViewport( x, y, width, height );
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    void OpenGLRendererAPI::SetLineWidth( float width )
    {
        glLineWidth( width );
    }
}
