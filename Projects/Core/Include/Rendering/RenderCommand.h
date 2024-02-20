#pragma once

#include <Rendering/RendererAPI.h>

namespace Ephemeral
{
    class RenderCommand
    {
    public:
        static void Init()
        {
            s_RendererAPI->Init();
        }

        static void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height )
        {
            s_RendererAPI->SetViewport( x, y, width, height );
        }

        static void Clear()
        {
            s_RendererAPI->Clear();
        }

        static void SetLineWidth( float width )
        {
            s_RendererAPI->SetLineWidth( width );
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };
}
