#pragma once

#ifndef EPH_CORE_VIEWPORT_H
#    define EPH_CORE_VIEWPORT_H

#    include <Core/Ephemeral.h>
#    include <Util/Math/Integer.h>

class Camera;

namespace Ephemeral
{
    class Viewport
    {
        friend class m1Render3D;
        friend class p1Scene;
        friend class p1ObjectEditor;

    public:
        Viewport();
        ~Viewport();

        void Begin() const;
        void End() const;

        void RenderOnImGui();

        void DrawGrid();
        bool drawGrid = true;

        inline Camera * GetCamera() const
        {
            return camera;
        }

    private:
        void Clear();

        void Update();
        void UpdateSize( int x, int y );
        void Blit() const;

        unsigned int GetTexture() const;

    public:
        float    color[3] = { .2f, .2f, .2f };
        Camera * camera   = nullptr;

    private:
        IntegerUtil size;

        enum FBOIDS
        {
            FBO,
            FBO_MS,
            TEXTURE,
            TEXTURE_MS,
            RBO,
            RBO_MS
        };

        unsigned int ID[6];
    };
}

#endif
