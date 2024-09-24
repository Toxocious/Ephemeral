#include <Core/Ephemeral.h>

#include <Modules/_Module.h>

#include <Modules/ImGuiLayer.h>

#include <Renderer/GameScene.h>
#include <Renderer/Imgui.h>

namespace Ephemeral
{
    ImGuiLayer::ImGuiLayer( bool enabled )
        : Module( "ImGuiLayer", enabled )
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
        CleanUp();
    }

    bool ImGuiLayer::Initialize()
    {
        return true;
    }

    bool ImGuiLayer::Start()
    {
        return true;
    }

    bool ImGuiLayer::CleanUp()
    {
        return true;
    }

    UpdateStatus ImGuiLayer::PreUpdate()
    {
        for ( Module * layer : m_Layers )
        {
            layer->PreUpdate();
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus ImGuiLayer::Update()
    {
        Ephemeral::Imgui::NewFrame();

        for ( Module * layer : m_Layers )
        {
            layer->Update();
        }

        Ephemeral::Imgui::RenderFrame();

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus ImGuiLayer::PostUpdate()
    {
        for ( Module * layer : m_Layers )
        {
            layer->PostUpdate();
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    void ImGuiLayer::PushLayer( Module * layer )
    {
        m_Layers.emplace_back( layer );
        layer->Initialize();
        layer->Start();
    }
}
