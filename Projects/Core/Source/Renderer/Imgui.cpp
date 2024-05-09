#include <Core/Ephemeral.h>

#include <Renderer/Imgui.h>

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ephemeral
{
    namespace Imgui
    {
        /**
         * Initialization and frame handlers.
         */
        void Initialize( GLFWwindow * m_Window )
        {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO & io = ImGui::GetIO();
            ( void ) io;

            // Set font size and add fonts.
            auto  fontPath = ( Global::GetCoreAssetPath() / "Fonts\\OpenSans\\OpenSans-Regular.ttf" ).string();
            float fontSize = 18.0f;
            io.Fonts->AddFontFromFileTTF( fontPath.c_str(), fontSize );
            io.FontDefault = io.Fonts->AddFontFromFileTTF( fontPath.c_str(), fontSize );

            // Set styling.
            SetDarkThemeColors();

            // Initialize Dear ImGui.
            ImGui_ImplGlfw_InitForOpenGL( m_Window, true );
            ImGui_ImplOpenGL3_Init( "#version 430" );
        }

        /**
         * Tell OpenGL a new frame is about to begin
         */
        void NewFrame()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        /**
         * Renders the ImGUI elements
         */
        void RenderFrame()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );
        }

        /**
         * Deletes all ImGUI instances
         */
        void Shutdown()
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }

        /**
         * Sets a custom dark theme
         */
        void SetDarkThemeColors()
        {
            ImGui::StyleColorsDark();

            auto & colors             = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4 { 0.1f, 0.105f, 0.11f, 1.0f };

            // Headers
            colors[ImGuiCol_Header]        = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_HeaderHovered] = ImVec4 { 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_HeaderActive]  = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };

            // Buttons
            colors[ImGuiCol_Button]        = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_ButtonHovered] = ImVec4 { 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_ButtonActive]  = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };

            // Frame BG
            colors[ImGuiCol_FrameBg]        = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };
            colors[ImGuiCol_FrameBgHovered] = ImVec4 { 0.3f, 0.305f, 0.31f, 1.0f };
            colors[ImGuiCol_FrameBgActive]  = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };

            // Tabs
            colors[ImGuiCol_Tab]                = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabHovered]         = ImVec4 { 0.38f, 0.3805f, 0.381f, 1.0f };
            colors[ImGuiCol_TabActive]          = ImVec4 { 0.28f, 0.2805f, 0.281f, 1.0f };
            colors[ImGuiCol_TabUnfocused]       = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4 { 0.2f, 0.205f, 0.21f, 1.0f };

            // Title
            colors[ImGuiCol_TitleBg]          = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgActive]    = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4 { 0.15f, 0.1505f, 0.151f, 1.0f };
        }

        void TextCentered( std::string text )
        {
            auto windowWidth = ImGui::GetWindowSize().x;
            auto textWidth   = ImGui::CalcTextSize( text.c_str() ).x;

            ImGui::SetCursorPosX( ( windowWidth - textWidth ) * 0.5f );
            ImGui::Text( text.c_str() );
        }
    };
}

