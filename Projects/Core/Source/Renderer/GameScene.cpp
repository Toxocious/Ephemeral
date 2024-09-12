#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Renderer/GameScene.h>
#include <Renderer/Viewport.h>

#include <imgui_internal.h>

ImVec2 operator+( const ImVec2 & lhs, const ImVec2 & rhs )
{
    return ImVec2( lhs.x + rhs.x, lhs.y + rhs.y );
}

namespace Ephemeral
{
    GameScene::GameScene()
    {
        EPH_CORE_ERROR( "new game scene" );
    }

    GameScene::~GameScene()
    {
    }

    void GameScene::CleanUp()
    {
    }

    void GameScene::Initialize()
    {
    }

    void GameScene::Start()
    {
        auto newScene = App->m_Renderer->CreateViewport( "Scene" );
        if ( newScene != nullptr )
        {
            m_SceneViewport = newScene;

            m_SceneViewport->m_Camera->isActive = true;
        }
    }

    void GameScene::Update()
    {
        // ImGui::Begin( "SceneWindow", nullptr, ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse );
        // {
        //     ImGui::PushClipRect( ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImGui::GetWindowSize(), false );

        //     ImGui::SetCursorScreenPos( ImGui::GetWindowPos() + ImVec2( 0, ImGui::GetCurrentWindow()->TitleBarHeight() + ImGui::GetCurrentWindow()->MenuBarHeight() ) );

        //     ImVec2 window_size = ImVec2( 1366.f, 768.f );

        //     {
        //         m_SceneViewport->UpdateSize( ( int ) window_size.x, ( int ) window_size.y );

        //         m_SceneViewport->Update();

        //         m_SceneViewport->Blit();
        //     }

        //     ImGui::Image( ( ImTextureID ) m_SceneViewport->GetTexture(), window_size, ImVec2( 0, 0 ), ImVec2( 1, -1 ) );

        //     ImGui::PopClipRect();
        // }
        // ImGui::End();
    }
}
