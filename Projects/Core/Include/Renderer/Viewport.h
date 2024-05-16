#pragma once

#ifndef EPH_CORE_VIEWPORT_H
#    define EPH_CORE_VIEWPORT_H

#    include <Core/Ephemeral.h>

#    include <Renderer/Camera.h>

#    include <Util/Math/Integer.h>

class Camera;

namespace Ephemeral
{
    class Viewport
    {
        friend class Renderer;
        friend class Camera;
        // friend class Scene;

    public:
        Viewport();
        ~Viewport();

        void Begin() const;
        void End() const;

        void Clear();

        void RenderOnImGui();

        void DrawGrid();
        bool m_ShowGrid = true;

        inline Camera * GetCamera() const
        {
            return m_Camera;
        }

    private:
        void Update();
        void UpdateSize( int x, int y );
        void Blit() const;

        unsigned int GetTexture() const;

    public:
        float    m_Color[3] = { .2f, .2f, .2f };
        Camera * m_Camera   = nullptr;

    private:
        IntegerUtil m_Size;

        enum FBOIDS
        {
            FBO,
            FBO_MS,
            TEXTURE,
            TEXTURE_MS,
            RBO,
            RBO_MS
        };

        unsigned int m_ID[6];
    };
}

#endif
