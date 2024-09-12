#include <Core/Ephemeral.h>

#include <Renderer/Imgui.h>

#include "Gui/Interface.h"

#include "Gui/Fonts/IconsFontAwesome5.h"
#include "Gui/Fonts/IconsFontAwesome5Brands.h"

#include "Gui/Panels/Scene.h"

#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Ephemeral
{
    EditorInterface::EditorInterface( bool enabled )
        : Module( "EditorInterface", enabled )
    {
        ImGuiIO & io = ImGui::GetIO();

        ImFontConfig icons_config;
        icons_config.MergeMode        = true;
        icons_config.PixelSnapH       = true;
        icons_config.GlyphMinAdvanceX = 13.0f;

        static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
        io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAS.c_str(), 12.0f, &icons_config, icons_ranges );

        static const ImWchar icons_ranges2[] = { ICON_MIN_FAB, ICON_MAX_FAB, 0 };
        io.Fonts->AddFontFromFileTTF( FONT_ICON_FILE_NAME_FAB.c_str(), 16.0f, &icons_config, icons_ranges2 );
    }

    EditorInterface::~EditorInterface()
    {
        CleanUp();
    }

    bool EditorInterface::Initialize()
    {
        // Instantiate and push editor gui modules to the interface.
        m_GuiModules.push_back( new EditorScene() );

        // Initialize all of our modules.
        for ( auto module = m_GuiModules.begin(); module != m_GuiModules.end(); ++module )
        {
            auto p_Module = ( *module );
            EPH_TRACE( "Initializing module '{0}'", p_Module->m_Name.c_str() );

            p_Module->Initialize();
        }

        return true;
    }

    bool EditorInterface::Start()
    {
        for ( auto module = m_GuiModules.begin(); module != m_GuiModules.end(); ++module )
        {
            auto p_Module = ( *module );
            EPH_TRACE( "Starting module '{0}'", p_Module->m_Name.c_str() );

            p_Module->Start();
        }

        return true;
    }

    bool EditorInterface::CleanUp()
    {
        for ( auto module = m_GuiModules.begin(); module != m_GuiModules.end(); ++module )
        {
            auto p_Module = ( *module );
            EPH_TRACE( "Cleaning up module '{0}'", p_Module->m_Name.c_str() );

            p_Module->CleanUp();
        }

        return true;
    }

    UpdateStatus EditorInterface::PreUpdate()
    {
        for ( auto module = m_GuiModules.begin(); module != m_GuiModules.end(); ++module )
        {
            auto p_Module = ( *module );
            p_Module->PreUpdate();
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus EditorInterface::Update()
    {
        PrepareDockspace();

        for ( auto module = m_GuiModules.begin(); module != m_GuiModules.end(); ++module )
        {
            auto p_Module = ( *module );

            ImGui::PushID( *module );

            ImGuiWindowFlags m_WindowFlags = ImGuiWindowFlags_None;
            if ( p_Module->m_Name == "EditorScene" )
            {
                m_WindowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration;
            }

            if ( ImGui::Begin( p_Module->m_Name.c_str(), 0, m_WindowFlags ) )
            {
                p_Module->Update();
            }
            ImGui::End();

            ImGui::PopID();
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus EditorInterface::PostUpdate()
    {
        for ( auto module = m_GuiModules.begin(); module != m_GuiModules.end(); ++module )
        {
            auto p_Module = ( *module );
            p_Module->PostUpdate();
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    void EditorInterface::PrepareDockspace()
    {
        const ImGuiViewport * viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos( viewport->Pos );
        ImGui::SetNextWindowSize( viewport->Size );
        ImGui::SetNextWindowViewport( viewport->ID );
        ImGui::SetNextWindowBgAlpha( 0.0f );

        ImGuiWindowFlags window_flags  = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        window_flags                  |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags                  |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
        ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
        ImGui::Begin( "DockSpace Demo", NULL, window_flags );
        {
            ImGui::PopStyleVar( 3 );

            ImGuiID            dockspace_id    = ImGui::GetID( "MyDockspace" );
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

            ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
        }
        ImGui::End();
    }
}
