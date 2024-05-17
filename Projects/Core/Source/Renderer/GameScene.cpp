#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Renderer/GameScene.h>
#include <Renderer/Viewport.h>

#include <imgui_internal.h>

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
        ImGui::Begin( "SceneWindow" );
        {
            ImGui::PushClipRect( ImGui::GetWindowPos(), ImVec2( ImGui::GetWindowPos().x + ImGui::GetWindowSize().x, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y ), false );

            ImGui::SetCursorScreenPos( ImVec2(
                ImGui::GetWindowPos().x + 0,
                ImGui::GetWindowSize().y + ImGui::GetCurrentWindow()->TitleBarHeight() + ImGui::GetCurrentWindow()->MenuBarHeight()
            ) );

            // ImGui::SetCursorScreenPos( ImGui::GetWindowPos() + ImVec2( 0, ImGui::GetCurrentWindow()->TitleBarHeight() + ImGui::GetCurrentWindow()->MenuBarHeight() ) );

            ImVec2 window_size = ImVec2(
                ImGui::GetContentRegionAvail().x + 16,
                ImGui::GetContentRegionAvail().y + 16
            );
            // ImVec2 window_size = ImGui::GetContentRegionAvail() + ImVec2( 16, 16 );

            m_SceneViewport->UpdateSize( ( int ) window_size.x, ( int ) window_size.y );

            m_SceneViewport->Update();

            m_SceneViewport->Blit();

            ImGui::Image( ( ImTextureID ) m_SceneViewport->GetTexture(), window_size, ImVec2( 0, 0 ), ImVec2( 1, -1 ) );

            ImGui::PopClipRect();
        }
        ImGui::End();
    }
}
