#include <Rendering/RendererAPI.h>

#include <Platforms/OpenGL/OpenGLContext.h>
#include <Platforms/OpenGL/OpenGLRenderAPI.h>

namespace Ephemeral
{
    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create()
    {
        return CreateScope<OpenGLRendererAPI>();
    }
}
