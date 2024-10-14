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
    public:
        Viewport( const char * name );
        ~Viewport();

        void Begin() const;
        void End() const;

        void Clear();

        inline Camera * GetCamera() const
        {
            return m_Camera;
        }

        void Update();
        void UpdateSize( int x, int y );
        void Blit() const;

        unsigned int GetTexture() const;

    public:
        void RenderOnImGui();

        void DrawGrid();

        void DrawTriangle();

    public:
        std::string m_Name;

        bool m_ShowGrid = true;

        Camera * m_Camera = nullptr;

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

        float m_Color[3] = { 0.269f, 0.420f, 0.625f };
    };
}

#endif
