#include <Core/Ephemeral.h>

#include <Modules/_Module.h>

#include <Modules/ImGuiLayer.h>

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
        EPH_CORE_TRACE( "Initializing imGuiLayer" );
        {
        }
        EPH_CORE_INFO( "ImGuiLayer initialized" );

        return true;
    }

    bool ImGuiLayer::Start()
    {
        return true;
    }

    UpdateStatus ImGuiLayer::PreUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus ImGuiLayer::PostUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus ImGuiLayer::Update()
    {
        Ephemeral::Imgui::NewFrame();
        {
            {
                for ( Module * layer : m_Layers )
                {
                    layer->Update();
                }
            }
        }
        Ephemeral::Imgui::RenderFrame();

        return UpdateStatus::UPDATE_CONTINUE;
    }

    bool ImGuiLayer::CleanUp()
    {
        return true;
    }

    void ImGuiLayer::PushLayer( Module * layer )
    {
        m_Layers.emplace_back( layer );
        layer->Initialize();
        layer->Start();
    }
}
