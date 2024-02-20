#include <Rendering/RenderCommand.h>

#include <Util/Base.h>

namespace Ephemeral
{
    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}
