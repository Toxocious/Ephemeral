#include <Core/Ephemeral.h>

#include "Gui/Interface.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ephemeral
{
    EditorInterface::EditorInterface( bool enabled )
        : Module( "EditorInterface", enabled )
    {
    }

    EditorInterface::~EditorInterface()
    {
        CleanUp();
    }

    bool EditorInterface::Initialize()
    {
        return true;
    }

    bool EditorInterface::Start()
    {
        return true;
    }

    bool EditorInterface::CleanUp()
    {
        return true;
    }

    UpdateStatus EditorInterface::Update()
    {
        ShowMenuBar();
        ShowDebugOverlay();
        ShowHudButtons();

        return UpdateStatus::UPDATE_CONTINUE;
    }

    void EditorInterface::ShowMenuBar()
    {
        if ( ImGui::BeginMainMenuBar() )
        {
            if ( ImGui::BeginMenu( "File" ) )
            {
                ImGui::EndMenu();
            }

            if ( ImGui::BeginMenu( "Edit" ) )
            {
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
    }

    void EditorInterface::ShowHudButtons()
    {
        ImGuiIO &        io           = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;

        const float           PAD       = 10.0f;
        const ImGuiViewport * viewport  = ImGui::GetMainViewport();
        ImVec2                work_pos  = viewport->Pos;
        ImVec2                work_size = viewport->Size;
        ImVec2                window_pos, window_pos_pivot;
        window_pos.x       = ( 1 & 1 ) ? ( work_pos.x + work_size.x - ( PAD * 0.5f ) ) : ( work_pos.x + ( PAD * 0.5f ) );
        window_pos.y       = work_pos.y + ( PAD * 2.75 );
        window_pos_pivot.x = ( 1 & 1 ) ? 1.0f : 0.0f;
        window_pos_pivot.y = ( 1 & 2 ) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos( window_pos, ImGuiCond_Always, window_pos_pivot );

        if ( ImGui::Begin( "Hud Buttons", nullptr, window_flags ) )
        {
            ImGui::PushStyleVar( ImGuiStyleVar_FrameRounding, 6.f );
            {
                ImGui::Button( "1", ImVec2( 30.f, 30.f ) );
                ImGui::Button( "2", ImVec2( 30.f, 30.f ) );
                ImGui::Button( "3", ImVec2( 30.f, 30.f ) );
                ImGui::Button( "4", ImVec2( 30.f, 30.f ) );
                ImGui::Button( "5", ImVec2( 30.f, 30.f ) );
            }
            ImGui::PopStyleVar();
        }
        ImGui::End();
    }

    void EditorInterface::ShowDebugOverlay()
    {
        ImGuiIO &        io           = ImGui::GetIO();
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;

        const float           PAD       = 10.0f;
        const ImGuiViewport * viewport  = ImGui::GetMainViewport();
        ImVec2                work_pos  = viewport->Pos;
        ImVec2                work_size = viewport->Size;
        ImVec2                window_pos, window_pos_pivot;
        window_pos.x       = ( 3 & 1 ) ? ( work_pos.x + work_size.x - PAD ) : ( work_pos.x + PAD );
        window_pos.y       = ( 3 & 2 ) ? ( work_pos.y + work_size.y - PAD ) : ( work_pos.y + PAD );
        window_pos_pivot.x = ( 3 & 1 ) ? 1.0f : 0.0f;
        window_pos_pivot.y = ( 3 & 2 ) ? 1.0f : 0.0f;
        ImGui::SetNextWindowPos( window_pos, ImGuiCond_Always, window_pos_pivot );

        ImGui::SetNextWindowBgAlpha( 0.35f );
        if ( ImGui::Begin( "FPS Overlay", nullptr, window_flags ) )
        {
            ImGui::Text( "(%.1f FPS)", ImGui::GetIO().Framerate );
        }
        ImGui::End();
    }
}
