#include <Core/Ephemeral.h>
#include <Rendering/RenderCommand.h>
#include <Rendering/Renderer.h>

namespace Ephemeral
{
    void Renderer::Init()
    {
        EPH_PROFILE_FUNCTION();

        RenderCommand::Init();
    }

    void Renderer::Shutdown()
    {
    }

    void Renderer::OnWindowResize( uint32_t width, uint32_t height )
    {
        RenderCommand::SetViewport( 0, 0, width, height );
    }
}
