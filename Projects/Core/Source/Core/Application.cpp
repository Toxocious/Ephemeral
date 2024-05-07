#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/_Module.h>

#include <Modules/ImGuiLayer.h>
#include <Modules/Window.h>

namespace Ephemeral
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    bool Application::Initialize( std::string name, std::string version, int height, int width )
    {
        EPH_CORE_TRACE( "Initializing Application" );
        {
            // Create instances of required modules.
            m_Window     = new Window();
            m_ImGuiLayer = new ImGuiLayer();

            // Assign order of execution to modules.
            m_Modules.push_back( m_Window );
            m_Modules.push_back( m_ImGuiLayer );

            // Initialize all of our modules.
            for ( auto module = m_Modules.begin(); module != m_Modules.end(); ++module )
            {
                auto p_Module = ( *module );
                EPH_CORE_TRACE( "Initializing module '{0}'", p_Module->m_Name.c_str() );

                if ( p_Module->m_Name == "Window" )
                {
                    p_Module->Initialize( height, width, name.c_str() );
                }
            }

            // Set the name, version, and dimensions of the application.
            m_Name    = name;
            m_Version = version;
            m_Height  = height;
            m_Width   = width;
        }
        EPH_CORE_TRACE( "Application initialized" );

        return true;
    }

    bool Application::Start()
    {
        EPH_CORE_TRACE( "Starting Application" );
        {
            // Start all of our modules.
            for ( auto module = m_Modules.begin(); module != m_Modules.end(); ++module )
            {
                auto p_Module = ( *module );
                EPH_CORE_TRACE( "Starting module '{0}'", p_Module->m_Name.c_str() );
                p_Module->Start();
            }
        }
        return true;
    }

    bool Application::CleanUp()
    {
        EPH_CORE_TRACE( "Cleaning up Application" );
        {
        }
        return true;
    }

    bool Application::PreUpdate()
    {
        EPH_CORE_TRACE( "Running Application Pre-Update" );
        {
        }
        return true;
    }

    UpdateStatus Application::Update()
    {
        // EPH_CORE_PROFILE();
        UpdateStatus status = UpdateStatus::UPDATE_CONTINUE;

        // Pre-Update
        {
            for ( auto module = m_Modules.begin(); module != m_Modules.end(); ++module )
            {
                auto p_Module = ( *module );

                status = p_Module->PreUpdate();
                if ( status != UpdateStatus::UPDATE_CONTINUE )
                {
                    EPH_CORE_ERROR( "Module '{0}' failed on PreUpdate() -> '{1}'", p_Module->m_Name, p_Module->UpdateStatusToString( status ).c_str() );

                    return status;
                }
            }
        }

        // Update
        {
            for ( auto module = m_Modules.begin(); module != m_Modules.end(); ++module )
            {
                auto p_Module = ( *module );

                status = p_Module->Update();
                if ( status != UpdateStatus::UPDATE_CONTINUE )
                {
                    EPH_CORE_ERROR( "Module '{0}' failed on Update() -> '{1}'", p_Module->m_Name, p_Module->UpdateStatusToString( status ).c_str() );

                    return status;
                }
            }
        }

        // Post-Update
        {
            for ( auto module = m_Modules.begin(); module != m_Modules.end(); ++module )
            {
                auto p_Module = ( *module );

                status = p_Module->PostUpdate();
                if ( status != UpdateStatus::UPDATE_CONTINUE )
                {
                    EPH_CORE_ERROR( "Module '{0}' failed on PostUpdate() -> '{1}'", p_Module->m_Name, p_Module->UpdateStatusToString( status ).c_str() );

                    return status;
                }
            }
        }

        PostUpdate();

        return status;
    }

    bool Application::PostUpdate()
    {
        return true;
    }

    void Application::PushLayer( Module * layer )
    {
        m_ImGuiLayer->PushLayer( layer );
    }
}
