#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/_Module.h>

#include <Modules/Renderer.h>

#include <Renderer/Imgui.h>
#include <Renderer/Shader.h>
#include <Renderer/Viewport.h>

#include <Util/FileSystem.h>

namespace Ephemeral
{
    Renderer::Renderer( bool enabled )
        : Module( "Renderer", enabled )
    {
    }

    Renderer::~Renderer()
    {
    }

    bool Renderer::Initialize()
    {
        auto window = App->m_Window->GetGLFWWindow();
        glfwMakeContextCurrent( window );

        int status = gladLoadGL();
        if ( !status )
        {
            EPH_CORE_ERROR( "Failed to initialize GLAD" );
            glfwTerminate();
            return false;
        }

        auto height = App->m_Window->GetHeight();
        auto width  = App->m_Window->GetWidth();

        glViewport( 0, 0, width, height );

        // glfwSwapInterval( 0 );

        Ephemeral::Imgui::Initialize( window );

        glEnable( GL_CULL_FACE );
        glCullFace( GL_FRONT );

        glEnable( GL_MULTISAMPLE );
        glEnable( GL_BLEND );
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

        glDepthFunc( GL_LEQUAL );

        LoadShaders();

        return true;
    }

    UpdateStatus Renderer::PreUpdate()
    {
        glClearColor( 0.15f, 0.15f, 0.15f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        for ( auto viewport = m_Viewports.begin(); viewport != m_Viewports.end(); ++viewport )
        {
            auto p_Viewport = ( *viewport ).second;

            p_Viewport->Clear();
            if ( p_Viewport->m_ShowGrid )
            {
                EPH_CORE_TRACE( "Drawing a grid in a viewport." );
                p_Viewport->DrawGrid();
            }
        }

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus Renderer::PostUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    bool Renderer::Start()
    {
        return true;
    }

    bool Renderer::CleanUp()
    {
        // Delete all viewports.
        for ( auto viewport = m_Viewports.begin(); viewport != m_Viewports.end(); ++viewport )
        {
            delete ( *viewport ).second;
        }

        // Delete all shaders.
        for ( auto shader : m_Shaders )
        {
            glDeleteShader( shader.second );
        }

        // Shutdown our ImGui layers.
        Ephemeral::Imgui::Shutdown();

        return true;
    }

    Viewport * Renderer::CreateViewport( const char * name )
    {
        Viewport * viewport = new Viewport();
        viewport->m_Camera  = App->m_SceneCamera->CreateCamera( name );

        m_Viewports[name] = viewport;

        return viewport;
    }

    /**
     * Fetch, load, and compile all shaders.
     */
    void Renderer::LoadShaders()
    {
        EPH_CORE_TRACE( "\t  Loading all shaders." );
        {
            std::filesystem::path shaderDirectory = FileSystem::GetCoreAssetPath() / "Shaders";

            Folder * shaderFolders = FileSystem::GetFolders( shaderDirectory.string() );

            for ( auto shaderFolder : shaderFolders->folders )
            {
                EPH_CORE_TRACE( "\t\tCompiling and linking shader '{0}'", shaderFolder->name.c_str() );

                Shader * shader = new Shader();
                shader->SetName( shaderFolder->name.c_str() );

                unsigned int vertexObject   = -1;
                unsigned int fragmentObject = -1;

                for ( auto shaderFile : shaderFolder->files )
                {
                    std::string shaderFilePath = ( shaderDirectory / shaderFolder->name / shaderFile.first ).string();

                    m_Shaders[shaderFile.first] = shader->Compile( shaderFilePath );

                    if ( m_Shaders[shaderFile.first] )
                    {
                        if ( shaderFile.first.find( ".vertex.glsl" ) != std::string::npos )
                        {
                            vertexObject = m_Shaders[shaderFile.first];
                        }
                        else if ( shaderFile.first.find( ".fragment.glsl" ) != std::string::npos )
                        {
                            fragmentObject = m_Shaders[shaderFile.first];
                        }
                    }
                }

                if ( vertexObject != -1 && fragmentObject != -1 )
                {
                    shader->Link( vertexObject, fragmentObject );
                    m_Programs[shaderFolder->name.c_str()] = shader;

                    EPH_CORE_TRACE( "\t\tSuccessfully compiled and linked shader '{0}'", shaderFolder->name.c_str() );
                }
                else
                {
                    EPH_CORE_WARN( "Unable to link shader '{0}' due to invalid vertex or fragment objects.", shaderFolder->name.c_str() );
                }
            }
        }
        EPH_CORE_TRACE( "\t  All shaders loaded." );
    }

    Shader * Renderer::GetShader( const char * name )
    {
        auto shaderProgram = m_Programs.find( name );
        return ( shaderProgram == m_Programs.end() ) ? nullptr : ( *shaderProgram ).second;
    }

    /**
     * Returns a viewport given a name.
     */
    Viewport * Renderer::GetViewport( const char * name )
    {
        return m_Viewports[name];
    }
}
