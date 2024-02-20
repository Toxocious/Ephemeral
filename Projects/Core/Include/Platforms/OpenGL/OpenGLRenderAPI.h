#pragma once

#include <Rendering/RendererAPI.h>

namespace Ephemeral
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) override;

        virtual void Clear() override;

        virtual void SetLineWidth( float width ) override;
    };
}
