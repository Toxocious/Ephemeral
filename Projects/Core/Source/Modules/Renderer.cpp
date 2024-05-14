#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/_Module.h>

#include <Modules/Renderer.h>

#include <Renderer/Imgui.h>
#include <Renderer/Viewport.h>

namespace Ephemeral
{
    Renderer::Renderer( bool start_enabled )
        : Module( "Renderer", start_enabled )
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

        return true;
    }

    UpdateStatus Renderer::PreUpdate()
    {
        glClearColor( 0.15f, 0.15f, 0.15f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

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
        Ephemeral::Imgui::Shutdown();

        return true;
    }

    Viewport * Renderer::CreateViewport( const char * name )
    {
        Viewport * viewport = new Viewport();

        // Set the viewport's camera.
        //   viewport->m_Camera = App->Camera->CreateCamera(name);

        m_Viewports[name] = viewport;

        return viewport;
    }

    Viewport * Renderer::GetViewport( const char * name )
    {
        return m_Viewports[name];
    }

    // void LoadShaders()
    // {
    //
    // }
}
