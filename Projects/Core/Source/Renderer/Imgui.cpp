#pragma once

#include <Core/Ephemeral.h>

#include <Renderer/Imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ephemeral
{
    namespace Imgui
    {
        void RenderFps()
        {
            ImGuiIO &        io           = ImGui::GetIO();
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;

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
            window_flags |= ImGuiWindowFlags_NoMove;

            ImGui::SetNextWindowBgAlpha( 0.35f );
            if ( ImGui::Begin( "FPS Overlay", nullptr, window_flags ) )
            {
                ImGui::Text( "(%.1f FPS)", ImGui::GetIO().Framerate );
            }
            ImGui::End();
        }

        /**
         * Initialization and frame handlers.
         */
        void Initialize( GLFWwindow * m_Window )
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO & io = ImGui::GetIO();
            ( void ) io;
            ImGui::StyleColorsDark();
            ImGui_ImplGlfw_InitForOpenGL( m_Window, true );
            ImGui_ImplOpenGL3_Init( "#version 430" );
        }

        void NewFrame()
        {
            // Tell OpenGL a new frame is about to begin
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        void RenderFrame()
        {
            // Renders the ImGUI elements
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
        }

        void Shutdown()
        {
            // Deletes all ImGUI instances
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    };
}

