#include <Rendering/FrameBuffer.h>

#include <Platforms/OpenGL/OpenGLFrameBuffer.h>

namespace Ephemeral
{
    Ref<Framebuffer> Framebuffer::Create( const FramebufferSpecification & spec )
    {
        return CreateRef<OpenGLFramebuffer>( spec );
    }
}

