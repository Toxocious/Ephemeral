// #include "Renderer/Renderer.h"

#include <Rendering/GraphicsContext.h>

#include <Platforms/OpenGL/OpenGLContext.h>

namespace Ephemeral
{
    Scope<GraphicsContext> GraphicsContext::Create( void * window )
    {
        return CreateScope<OpenGLContext>( static_cast<GLFWwindow *>( window ) );
    }
}
