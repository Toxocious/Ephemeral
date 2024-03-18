#include "EditorLayer.h"

#include <Events/Input.h>
#include <Rendering/ImGui.hpp>
#include <Util/PlatformUtils.h>

#include <assert.h>
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

// #include "ImGuizmo.h"

namespace Ephemeral
{
    EditorLayer::EditorLayer()
        : Layer( "EditorLayer" )
    {
    }

    void EditorLayer::OnAttach()
    {
        EPH_PROFILE_FUNCTION();
    }

    void EditorLayer::OnDetach()
    {
        EPH_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate( Timestep ts )
    {
        EPH_PROFILE_FUNCTION();

        /**
         * Do I need this?
         * Ideally, the scene is always in an edit or play state.
         *  -> Edit state being able to place tiles, objects, etc.
         *  -> Play state being able to play the currently active map/scene.
         *
         * Do I want to make the editor only have edit mode, and play test maps in the _Projects/Game_ project (runs the game)?
         * Seems.. odd to do that, but may be less work?
         */
        switch ( m_SceneState )
        {
            case SceneState::Edit:
                {
                    break;
                }

            case SceneState::Play:
                {
                    break;
                }
        }

        auto [mx, my] = ImGui::GetMousePos();
        int mouseX    = ( int ) mx;
        int mouseY    = ( int ) my;

        OnOverlayRender();
    }

    void EditorLayer::OnImGuiRender()
    {
        EPH_PROFILE_FUNCTION();

        static bool               dockspaceOpen             = true;
        static bool               opt_fullscreen_persistant = true;
        bool                      opt_fullscreen            = opt_fullscreen_persistant;
        static ImGuiDockNodeFlags dockspace_flags           = ImGuiDockNodeFlags_None;
        ImGuiWindowFlags          window_flags              = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;

        ImGuiViewport * viewport = ImGui::GetMainViewport();
        if ( opt_fullscreen )
        {
            ImGui::SetNextWindowPos( viewport->Pos );
            ImGui::SetNextWindowSize( viewport->Size );
            ImGui::SetNextWindowViewport( viewport->ID );
            ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
            ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and
        // handle the pass-through hole, so we ask Begin() to not render a background.
        if ( dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode )
        {
            window_flags |= ImGuiWindowFlags_NoBackground;
        }

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );
        ImGui::Begin( "DockSpace Demo", &dockspaceOpen, window_flags );
        ImGui::PopStyleVar();

        if ( opt_fullscreen )
        {
            ImGui::PopStyleVar( 2 );
        }

        // DockSpace
        ImGuiIO &    io          = ImGui::GetIO();
        ImGuiStyle & style       = ImGui::GetStyle();
        float        minWinSizeX = style.WindowMinSize.x;
        style.WindowMinSize.x    = 370.0f;
        if ( io.ConfigFlags & ImGuiConfigFlags_DockingEnable )
        {
            ImGuiID dockspace_id = ImGui::GetID( "MyDockSpace" );
            ImGui::DockSpace( dockspace_id, ImVec2( 0.0f, 0.0f ), dockspace_flags );
        }

        style.WindowMinSize.x = minWinSizeX;

        // Draw to the application
        // DrawMenuBar();

        /**
         * Editor Scene Viewport
         */
        ImGui::SetNextWindowPos( viewport->Pos );
        ImGui::SetNextWindowSize( viewport->Size );
        ImGui::SetNextWindowViewport( viewport->ID );
        ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2 { 0, 0 } );
        ImGui::Begin( "Viewport", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize );
        {
            auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
            auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
            auto viewportOffset    = ImGui::GetWindowPos();
            m_ViewportBounds[0]    = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
            m_ViewportBounds[1]    = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

            m_ViewportFocused = ImGui::IsWindowFocused();
            m_ViewportHovered = ImGui::IsWindowHovered();

            Application::Get().GetImGuiLayer()->BlockEvents( !m_ViewportHovered );

            ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
            m_ViewportSize           = { viewportPanelSize.x, viewportPanelSize.y };

            // uint64_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
            // ImGui::Image( reinterpret_cast<void *>( textureID ), m_ViewportSize, ImVec2 { 0, 1 }, ImVec2 { 1, 0 } );

            /**
             * ImGui Overlays
             */
            Ephemeral::Rendering::Overlay::Debug_Stats( viewportPanelSize.x, viewportPanelSize.y );
        }
        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End();
    }

    void EditorLayer::OnEvent( Event & e )
    {
        // m_CameraController.OnEvent( e );
        // if ( m_SceneState == SceneState::Edit )
        // {
        //     m_EditorCamera.OnEvent( e );
        // }

        EventDispatcher dispatcher( e );
        dispatcher.Dispatch<KeyPressedEvent>( EPH_BIND_EVENT_FN( EditorLayer::OnKeyPressed ) );
        dispatcher.Dispatch<MouseButtonPressedEvent>( EPH_BIND_EVENT_FN( EditorLayer::OnMouseButtonPressed ) );
    }

    bool EditorLayer::OnKeyPressed( KeyPressedEvent & e )
    {
        if ( e.IsRepeat() )
        {
            return false;
        }

        bool control = Ephemeral::Input::IsKeyPressed( Key::LeftControl ) || Ephemeral::Input::IsKeyPressed( Key::RightControl );
        bool shift   = Ephemeral::Input::IsKeyPressed( Key::LeftShift ) || Ephemeral::Input::IsKeyPressed( Key::RightShift );

        switch ( e.GetKeyCode() )
        {
            // case Key::N:
            //     {
            //         if ( control )
            //         {
            //             NewScene();
            //         }

            //         break;
            //     }
            // case Key::O:
            //     {
            //         if ( control )
            //         {
            //             OpenProject();
            //         }

            //         break;
            //     }
            // case Key::S:
            //     {
            //         if ( control )
            //         {
            //             if ( shift )
            //             {
            //                 SaveSceneAs();
            //             }
            //             else
            //             {
            //                 SaveScene();
            //             }
            //         }

            //         break;
            //     }

            // Scene Commands
            // case Key::D:
            //     {
            //         if ( control )
            //         {
            //             OnDuplicateEntity();
            //         }

            //         break;
            //     }

            // Gizmos
            // case Key::Q:
            //     {
            //         if ( !ImGuizmo::IsUsing() )
            //         {
            //             m_GizmoType = -1;
            //         }
            //         break;
            //     }
            // case Key::W:
            //     {
            //         if ( !ImGuizmo::IsUsing() )
            //         {
            //             m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            //         }
            //         break;
            //     }
            // case Key::E:
            //     {
            //         if ( !ImGuizmo::IsUsing() )
            //         {
            //             m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            //         }
            //         break;
            //     }
            // case Key::R:
            //     {
            //         if ( control )
            //         {
            //             ScriptEngine::ReloadAssembly();
            //         }
            //         else
            //         {
            //             if ( !ImGuizmo::IsUsing() )
            //             {
            //                 m_GizmoType = ImGuizmo::OPERATION::SCALE;
            //             }
            //         }
            //         break;
            //     }
            // case Key::Delete:
            //     {
            //         if ( Application::Get().GetImGuiLayer()->GetActiveWidgetID() == 0 )
            //         {
            //             Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
            //             if ( selectedEntity )
            //             {
            //                 m_SceneHierarchyPanel.SetSelectedEntity( {} );
            //                 m_ActiveScene->DestroyEntity( selectedEntity );
            //             }
            //         }
            //         break;
            //     }
        }

        return false;
    }

    bool EditorLayer::OnMouseButtonPressed( MouseButtonPressedEvent & e )
    {
        if ( e.GetMouseButton() == Mouse::ButtonLeft )
        {
            // if ( m_ViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed( Key::LeftAlt ) )
            // {
            //     m_SceneHierarchyPanel.SetSelectedEntity( m_HoveredEntity );
            // }
        }
        return false;
    }

    void EditorLayer::OnOverlayRender()
    {
        if ( m_SceneState == SceneState::Play )
        {
            // Entity camera = m_ActiveScene->GetPrimaryCameraEntity();
            // if ( !camera )
            // {
            //     return;
            // }

            // Renderer2D::BeginScene( camera.GetComponent<CameraComponent>().Camera, camera.GetComponent<TransformComponent>().GetTransform() );
        }
        else
        {
            // Renderer2D::BeginScene( m_EditorCamera );
        }

        if ( m_ShowPhysicsColliders )
        {
            // Box Colliders
            {
                // auto view = m_ActiveScene->GetAllEntitiesWith<TransformComponent, BoxCollider2DComponent>();
                // for ( auto entity : view )
                // {
                //     auto [tc, bc2d] = view.get<TransformComponent, BoxCollider2DComponent>( entity );

                //     glm::vec3 translation = tc.Translation + glm::vec3( bc2d.Offset, 0.001f );
                //     glm::vec3 scale       = tc.Scale * glm::vec3( bc2d.Size * 2.0f, 1.0f );

                //     glm::mat4 transform = glm::translate( glm::mat4( 1.0f ), tc.Translation ) * glm::rotate( glm::mat4( 1.0f ), tc.Rotation.z, glm::vec3( 0.0f, 0.0f, 1.0f ) ) * glm::translate( glm::mat4( 1.0f ), glm::vec3( bc2d.Offset, 0.001f ) ) * glm::scale( glm::mat4( 1.0f ), scale );

                //     Renderer2D::DrawRect( transform, glm::vec4( 0, 1, 0, 1 ) );
                // }
            }
        }

        // Draw selected entity outline
        // if ( Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity() )
        // {
        //     const TransformComponent & transform = selectedEntity.GetComponent<TransformComponent>();
        //     Renderer2D::DrawRect( transform.GetTransform(), glm::vec4( 1.0f, 0.5f, 0.0f, 1.0f ) );
        // }

        // Renderer2D::EndScene();
    }

    void EditorLayer::NewProject()
    {
        // Project::New();
    }

    void EditorLayer::OpenProject( const std::filesystem::path & path )
    {
        // if ( Project::Load( path ) )
        // {
        //     ScriptEngine::Init();

        //     auto startScenePath = Project::GetAssetFileSystemPath( Project::GetActive()->GetConfig().StartScene );
        //     OpenScene( startScenePath );
        //     m_ContentBrowserPanel = CreateScope<ContentBrowserPanel>();
        // }
    }

    bool EditorLayer::OpenProject()
    {
        // std::string filepath = FileDialogs::OpenFile( "Ephemeral Project (*.hproj)\0*.hproj\0" );
        // if ( filepath.empty() )
        // {
        //     return false;
        // }

        // OpenProject( filepath );
        return true;
    }

    void EditorLayer::SaveProject()
    {
        // Project::SaveActive();
    }

    void EditorLayer::NewScene()
    {
        // m_ActiveScene = CreateRef<Scene>();
        // m_SceneHierarchyPanel.SetContext( m_ActiveScene );

        // m_EditorScenePath = std::filesystem::path();
    }

    void EditorLayer::OpenScene()
    {
        // std::string filepath = FileDialogs::OpenFile( "Ephemeral Scene (*.ephemeral)\0*.ephemeral\0" );
        // if ( !filepath.empty() )
        // {
        //     OpenScene( filepath );
        // }
    }

    void EditorLayer::OpenScene( const std::filesystem::path & path )
    {
        if ( m_SceneState != SceneState::Edit )
        {
            OnSceneStop();
        }

        if ( path.extension().string() != ".ephemeral" )
        {
            EPH_WARN( "Could not load {0} - not a scene file", path.filename().string() );
            return;
        }

        // Ref<Scene>      newScene = CreateRef<Scene>();
        // SceneSerializer serializer( newScene );
        // if ( serializer.Deserialize( path.string() ) )
        // {
        //     m_EditorScene = newScene;
        //     m_SceneHierarchyPanel.SetContext( m_EditorScene );

        //     m_ActiveScene     = m_EditorScene;
        //     m_EditorScenePath = path;
        // }
    }

    void EditorLayer::SaveScene()
    {
        // if ( !m_EditorScenePath.empty() )
        // {
        //     SerializeScene( m_ActiveScene, m_EditorScenePath );
        // }
        // else
        // {
        //     SaveSceneAs();
        // }
    }

    void EditorLayer::SaveSceneAs()
    {
        // std::string filepath = FileDialogs::SaveFile( "Ephemeral Scene (*.ephemeral)\0*.ephemeral\0" );
        // if ( !filepath.empty() )
        // {
        //     SerializeScene( m_ActiveScene, filepath );
        //     m_EditorScenePath = filepath;
        // }
    }

    // Writes scene file to disk.
    // void EditorLayer::SerializeScene( Ref<Scene> scene, const std::filesystem::path & path )
    // {
    //     SceneSerializer serializer( scene );
    //     serializer.Serialize( path.string() );
    // }

    void EditorLayer::OnScenePlay()
    {
        m_SceneState = SceneState::Play;

        // m_ActiveScene = Scene::Copy( m_EditorScene );
        // m_ActiveScene->OnRuntimeStart();

        // m_SceneHierarchyPanel.SetContext( m_ActiveScene );
    }

    void EditorLayer::OnSceneStop()
    {
        EPH_CORE_ASSERT( m_SceneState == SceneState::Play );

        if ( m_SceneState == SceneState::Play )
        {
            // m_ActiveScene->OnRuntimeStop();
        }

        m_SceneState = SceneState::Edit;

        // m_ActiveScene = m_EditorScene;

        // m_SceneHierarchyPanel.SetContext( m_ActiveScene );
    }

    void EditorLayer::OnScenePause()
    {
        if ( m_SceneState == SceneState::Edit )
        {
            return;
        }

        // m_ActiveScene->SetPaused( true );
    }

    void EditorLayer::OnDuplicateEntity()
    {
        if ( m_SceneState != SceneState::Edit )
        {
            return;
        }

        // Entity selectedEntity = m_SceneHierarchyPanel.GetSelectedEntity();
        // if ( selectedEntity )
        // {
        //     Entity newEntity = m_EditorScene->DuplicateEntity( selectedEntity );
        //     m_SceneHierarchyPanel.SetSelectedEntity( newEntity );
        // }
    }

    /**
     * Functions that draw to the application
     */

    void EditorLayer::DrawMenuBar()
    {
        ImGui::BeginMenuBar();
        {
            if ( ImGui::BeginMenu( "File" ) )
            {
                if ( ImGui::MenuItem( "Open Project...", "Ctrl+O" ) )
                {
                    OpenProject();
                }

                ImGui::Separator();

                if ( ImGui::MenuItem( "New Scene", "Ctrl+N" ) )
                {
                    NewScene();
                }

                if ( ImGui::MenuItem( "Save Scene", "Ctrl+S" ) )
                {
                    SaveScene();
                }

                if ( ImGui::MenuItem( "Save Scene As...", "Ctrl+Shift+S" ) )
                {
                    SaveSceneAs();
                }

                ImGui::Separator();

                if ( ImGui::MenuItem( "Exit" ) )
                {
                    Application::Get().Close();
                }

                ImGui::EndMenu();
            }
        }
        ImGui::EndMenuBar();
    }

    void EditorLayer::DrawGrid()
    {
        const float CELL_SIZE = 1.f;

        glColor3f( 1.0f, 1.0f, 1.0f ); // Set color to white
        glBegin( GL_LINES );
        for ( float i = -1.0f; i <= 1.0f; i += CELL_SIZE )
        {
            glVertex2f( i, -1.0f ); // Vertical lines
            glVertex2f( i, 1.0f );

            glVertex2f( -1.0f, i ); // Horizontal lines
            glVertex2f( 1.0f, i );
        }
        glEnd();
    }
}
