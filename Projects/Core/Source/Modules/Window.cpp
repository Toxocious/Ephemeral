#include <Core/Ephemeral.h>

#include <Modules/Window.h>

#include <Renderer/Imgui.h>

#include <stb_image/stb_image.h>

namespace Ephemeral
{
    Window::Window( bool enabled )
        : Module( "Window", enabled ), m_Window( nullptr, &glfwDestroyWindow )
    {
    }

    Window::~Window()
    {
        CleanUp();
    }

    bool Window::Initialize( const int height, const int width, const char * title )
    {
        if ( !glfwInit() )
        {
            EPH_CORE_ERROR( "Failed to initialize GLFW" );
            return false;
        }

        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );
        glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE );
        glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );

        m_Window.reset( glfwCreateWindow( width, height, title, nullptr, nullptr ) );
        if ( !m_Window )
        {
            EPH_CORE_ERROR( "Failed to create the GLFW window" );
            glfwTerminate();
            return false;
        }

        glfwMakeContextCurrent( GetGLFWWindow() );
        // glfwSwapInterval( 0 );

        int status = gladLoadGL();
        if ( !status )
        {
            EPH_CORE_ERROR( "Failed to initialize GLAD" );
            glfwTerminate();
            return false;
        }

        int  iconWidth, iconHeight, channels;
        auto iconFilePath = ( Global::GetCoreAssetPath() / "Ephemeral.png" ).string();
        m_WindowIcon      = stbi_load( iconFilePath.c_str(), &iconWidth, &iconHeight, &channels, 0 );

        if ( m_WindowIcon != nullptr )
        {
            GLFWimage images[1];
            images[0].pixels = stbi_load( iconFilePath.c_str(), &images[0].width, &images[0].height, 0, 4 );
            glfwSetWindowIcon( GetGLFWWindow(), 1, images );
        }

        CenterWindow();

        m_Height = height;
        m_Width  = width;
        m_Title  = title;

        glViewport( 0, 0, m_Width, m_Height );

        Ephemeral::Imgui::Initialize( GetGLFWWindow() );

        return true;
    }

    bool Window::Start()
    {
        return true;
    }

    UpdateStatus Window::PreUpdate()
    {
        // Clear the background color.
        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // Enable depth testing.
        glEnable( GL_DEPTH_TEST );

        // Set wireframing.
        // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus Window::PostUpdate()
    {
        SwapBuffers();
        PollEvents();

        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus Window::Update()
    {
        if ( ShouldClose() )
        {
            return UpdateStatus::UPDATE_STOP;
        }

        // Ephemeral::Imgui::NewFrame();
        {
            {
                // Ephemeral::Imgui::RenderFps();
            }
        }
        // Ephemeral::Imgui::RenderFrame();

        return UpdateStatus::UPDATE_CONTINUE;
    }

    bool Window::CleanUp()
    {
        Ephemeral::Imgui::Shutdown();

        stbi_image_free( m_WindowIcon );
        glfwDestroyWindow( GetGLFWWindow() );
        glfwTerminate();

        return true;
    }

    int Window::GetHeight() const
    {
        return m_Height;
    }

    int Window::GetWidth() const
    {
        return m_Width;
    }

    void Window::SetWindowSize( const int & height, const int & width )
    {
        m_Height = height;
        m_Width  = width;
    }

    void Window::UpdateWindowSize()
    {
        glfwSetWindowSize( GetGLFWWindow(), m_Width, m_Height );
    }

    GLFWwindow * Window::GetGLFWWindow()
    {
        return m_Window.get();
    }

    void Window::CenterWindow()
    {
        int window_x, window_y;
        glfwGetWindowPos( GetGLFWWindow(), &window_x, &window_y );

        int window_width, window_height;
        glfwGetWindowSize( GetGLFWWindow(), &window_width, &window_height );

        window_width  *= 0.5;
        window_height *= 0.5;

        window_x += window_width;
        window_y += window_height;

        int            monitors_length;
        GLFWmonitor ** monitors = glfwGetMonitors( &monitors_length );

        if ( monitors == NULL )
        {
            return;
        }

        GLFWmonitor * owner = NULL;
        int           owner_x, owner_y, owner_width, owner_height;

        for ( int i = 0; i < monitors_length; i++ )
        {
            int monitor_x, monitor_y;
            glfwGetMonitorPos( monitors[i], &monitor_x, &monitor_y );

            int           monitor_width, monitor_height;
            GLFWvidmode * monitor_vidmode = ( GLFWvidmode * ) glfwGetVideoMode( monitors[i] );

            if ( monitor_vidmode == NULL )
            {
                continue;
            }
            else
            {
                monitor_width  = monitor_vidmode->width;
                monitor_height = monitor_vidmode->height;
            }

            if ( ( window_x > monitor_x && window_x < ( monitor_x + monitor_width ) ) && ( window_y > monitor_y && window_y < ( monitor_y + monitor_height ) ) )
            {
                owner = monitors[i];

                owner_x = monitor_x;
                owner_y = monitor_y;

                owner_width  = monitor_width;
                owner_height = monitor_height;
            }
        }

        if ( owner != NULL )
        {
            glfwSetWindowPos( GetGLFWWindow(), owner_x + ( owner_width * 0.5 ) - window_width, owner_y + ( owner_height * 0.5 ) - window_height );
        }
    }

    int Window::ShouldClose()
    {
        return glfwWindowShouldClose( GetGLFWWindow() );
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers( GetGLFWWindow() );
    }

    void Window::PollEvents()
    {
        return glfwPollEvents();
    }
}
