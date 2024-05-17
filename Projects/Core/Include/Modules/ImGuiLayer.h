#pragma once

#ifndef EPH_CORE_IMGUI_LAYER_H
#    define EPH_CORE_IMGUI_LAYER_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

namespace Ephemeral
{
    class GameScene;

    class ImGuiLayer : public Module
    {
    public:
        ImGuiLayer( bool enabled = true );
        ~ImGuiLayer();

    public:
        bool Initialize() override;
        bool Start() override;
        bool CleanUp() override;

        UpdateStatus PreUpdate() override;
        UpdateStatus Update() override;
        UpdateStatus PostUpdate() override;

        void PushLayer( Module * layer );

    private:
        std::vector<Module *> m_Layers;

        GameScene * m_GameScene = nullptr;
    };
}

#endif
