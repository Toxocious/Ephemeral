#pragma once

#ifndef EPH_EDITOR_SCENE_H
#    define EPH_EDITOR_SCENE_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

#    include <glm/vec2.hpp>
#    include <imgui.h>

namespace Ephemeral
{
    enum class SceneState
    {
        EDIT,
        PLAY,
    };

    class Viewport;

    class EditorScene : public Module
    {
    public:
        EditorScene( bool enabled = true );
        ~EditorScene();

    private:
        bool Initialize() override;
        bool Start() override;
        bool CleanUp() override;

        UpdateStatus PreUpdate() override;
        UpdateStatus Update() override;
        UpdateStatus PostUpdate() override;

    public:
        void RenderSceneMenuBar();
        void RenderNewMapModal();

        void RenderToolButtons();

    private:
        Viewport * m_Viewport = nullptr;

        SceneState m_SceneState = SceneState::EDIT;

        glm::vec2 m_ViewportBounds[2];

        bool m_showNewMapPopup = false;
    };
}

#endif
