#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Util/Math/ImVec.h>

#include <Renderer/Imgui.h>

#include "Gui/Fonts/IconsFontAwesome5.h"
#include "Gui/Fonts/IconsFontAwesome5Brands.h"

#include "Gui/Panels/EditorScene.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ephemeral
{
    EditorScene::EditorScene( bool enabled )
        : Module( "EditorScene", enabled )
    {
        // m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
    }

    EditorScene::~EditorScene()
    {
        CleanUp();
    }

    bool EditorScene::Initialize()
    {
        m_Viewport = App->m_Renderer->CreateViewport( "EditorSceneViewport" );

        m_Viewport->m_Camera->isActive = true;

        return true;
    }

    bool EditorScene::Start()
    {
        return true;
    }

    bool EditorScene::CleanUp()
    {
        return true;
    }

    UpdateStatus EditorScene::PreUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus EditorScene::Update()
    {
        RenderSceneMenuBar();
        if ( m_showNewMapPopup )
        {
            RenderNewMapModal();
        }

        // Render additional GUI panels and whatever.
        {
            // Begin the child window with the available space dimensions
            // ImGui::BeginChild( "Child Window", ImGui::GetContentRegionAvail(), true );
            // ImGui::Text( "This child window fills the remaining space." );
            // ImGui::EndChild();
        }

        // Render map scene.
        {
            {
                ImGui::PushClipRect( ImGui::GetWindowPos(), ImGui::GetWindowPos() + ImGui::GetWindowSize(), false );
                ImGui::SetCursorScreenPos( ImGui::GetWindowPos() + ImVec2( 0.f, 0.f ) );

                auto windowSize = ImGui::GetContentRegionAvail() + ImVec2( 8.f, 8.f );

                m_Viewport->UpdateSize( ( int ) windowSize.x, ( int ) windowSize.y );
                m_Viewport->Update();
                m_Viewport->Blit();

                ImGui::Image( ( ImTextureID ) m_Viewport->GetTexture(), windowSize, ImVec2( 0, 0 ), ImVec2( 1, -1 ) );

                ImGui::PopClipRect();
            }
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus EditorScene::PostUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    /**
     *
     */

    void EditorScene::RenderSceneMenuBar()
    {
        ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
        ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 8.0f, 8.f ) );

        if ( ImGui::BeginMainMenuBar() )
        {
            if ( ImGui::BeginMenu( "Map" ) )
            {
                {
                    if ( ImGui::MenuItem( "New Map", "CTRL + N" ) )
                    {
                        m_showNewMapPopup = true;
                    }

                    ImGui::MenuItem( "Save Map (Local)", "CTRL + S" );
                    ImGui::MenuItem( "Load Map (Local)", "CTRL + L" );
                }
                ImGui::Separator();
                {
                    ImGui::MenuItem( "Load Map From Server" );
                    ImGui::MenuItem( "Upload Map To Server" );
                }
                ImGui::EndMenu();
            }

            if ( ImGui::BeginMenu( "Edit" ) )
            {
                ImGui::EndMenu();
            }

            // Map Name
            Ephemeral::Imgui::TextCentered( "New Map" );

            // Right aligned menu objects
            ImGui::SetCursorPosX( ImGui::GetCursorPosX() + ImGui::GetContentRegionAvail().x - 60.f );
            {
                // ImGui::Text( "beep" );
            }

            // Custom bottom border line.
            // Get the draw list for the current window
            ImDrawList * draw_list = ImGui::GetWindowDrawList();

            // Get the position and size of the menubar
            ImVec2 pos  = ImGui::GetWindowPos();
            ImVec2 size = ImGui::GetWindowSize();

            // Draw the bottom border line
            draw_list->AddLine(
                ImVec2( pos.x, pos.y + size.y - 1 ),                        // Start point (bottom-left)
                ImVec2( pos.x + size.x, pos.y + size.y - 1 ),               // End point (bottom-right)
                ImGui::GetColorU32( ImVec4( 0.08f, 0.10f, 0.12f, 1.00f ) ), // Border color
                1.0f                                                        // Border thickness
            );

            ImGui::EndMainMenuBar();
        }

        ImGui::PopStyleVar( 2 );
    }

    void EditorScene::RenderNewMapModal()
    {
        ImGui::OpenPopup( "Create New Map?" );

        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos( center, ImGuiCond_Appearing, ImVec2( 0.5f, 0.5f ) );

        if ( ImGui::BeginPopupModal( "Create New Map?", NULL, ImGuiWindowFlags_AlwaysAutoResize ) )
        {
            ImGui::Text( "Creating a new map will unload the current map and not preserve any unsaved changes.\n\nAre you sure you want to discard any unsaved changes and create a new map?\n" );

            ImGui::Separator();

            if ( ImGui::Button( "Yes", ImVec2( 120, 0 ) ) )
            {
                // create a new map and close the popup
            }
            ImGui::SameLine();
            if ( ImGui::Button( "Cancel", ImVec2( 120, 0 ) ) )
            {
                m_showNewMapPopup = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
}
