#pragma once

#ifndef EPH_CORE_SCENE_H
#    define EPH_CORE_SCENE_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

#    include <Renderer/Viewport.h>

namespace Ephemeral
{
    class Scene : public Module
    {
    public:
        Scene( bool enabled = true );
        ~Scene();

        bool CleanUp() override;

        bool Initialize() override;
        bool Start() override;

        UpdateStatus Update() override;

    private:
        Viewport * m_SceneViewport = nullptr;
    };
}

#endif
