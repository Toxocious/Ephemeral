#pragma once

#ifndef EPH_CORE_GAME_SCENE_H
#    define EPH_CORE_GAME_SCENE_H

#    include <Core/Ephemeral.h>

#    include <Renderer/Viewport.h>

namespace Ephemeral
{
    class GameScene
    {
    public:
        GameScene();
        ~GameScene();

        void CleanUp();

        void Initialize();
        void Start();

        void Update();

    public:
        Viewport * m_SceneViewport = nullptr;
    };
}

#endif
