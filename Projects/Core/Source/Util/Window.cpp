#include <Core/Ephemeral.h>

#include <Util/Window.h>

#include <Modules/Imgui.h>

namespace Ephemeral
{
    Window::Window( int height, int width, const char * title )
        : m_Height( height ), m_Width( width ), m_Title( title ), m_Window( nullptr, &glfwDestroyWindow )
    {
        if ( !glfwInit() )
        {
            EPH_CORE_ERROR( "Failed to initialize GLFW" );
            return;
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
            return;
        }

        glfwMakeContextCurrent( m_Window.get() );
        glfwSwapInterval( 0 );

        int status = gladLoadGL();
        if ( !status )
        {
            EPH_CORE_ERROR( "Failed to initialize GLAD" );
            glfwTerminate();
            return;
        }

        CenterWindow();

        glViewport( 0, 0, m_Width, m_Height );

        EPH_CORE_TRACE( "Successfully initialized GLFW and GLAD, and created a window." );

        Ephemeral::Imgui::Initialize( m_Window.get() );
    }

    Window::~Window()
    {
        Ephemeral::Imgui::Shutdown();

        // Clean up resources

        // Terminate GLFW
        glfwDestroyWindow( m_Window.get() );
        glfwTerminate();
    }

    void Window::Run()
    {
        // Gets ID of uniform called "scale"
        while ( !ShouldClose() )
        {
            Ephemeral::Imgui::NewFrame();

            {
                // Clear the colorbuffer
                glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                // Set wireframing
                // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

                // Enable depth testing
                glEnable( GL_DEPTH_TEST );

                // Draw the triangle
                glDrawArrays( GL_TRIANGLES, 0, 3 );

                {
                    Ephemeral::Imgui::RenderFps();
                }
            }

            Ephemeral::Imgui::RenderFrame();

            // Swap the screen buffers
            SwapBuffers();

            // Check and call events
            PollEvents();
        }
    }

    // Centers the window on the user's monitor.
    // Credits: https://github.com/glfw/glfw/issues/310#issuecomment-52048508
    void Window::CenterWindow()
    {
        const auto window = m_Window.get();

        // Get window position and size
        int window_x, window_y;
        glfwGetWindowPos( window, &window_x, &window_y );

        int window_width, window_height;
        glfwGetWindowSize( window, &window_width, &window_height );

        // Halve the window size and use it to adjust the window position to the center of the window
        window_width  *= 0.5;
        window_height *= 0.5;

        window_x += window_width;
        window_y += window_height;

        // Get the list of monitors
        int            monitors_length;
        GLFWmonitor ** monitors = glfwGetMonitors( &monitors_length );

        if ( monitors == NULL )
        {
            // Got no monitors back
            return;
        }

        // Figure out which monitor the window is in
        GLFWmonitor * owner = NULL;
        int           owner_x, owner_y, owner_width, owner_height;

        for ( int i = 0; i < monitors_length; i++ )
        {
            // Get the monitor position
            int monitor_x, monitor_y;
            glfwGetMonitorPos( monitors[i], &monitor_x, &monitor_y );

            // Get the monitor size from its video mode
            int           monitor_width, monitor_height;
            GLFWvidmode * monitor_vidmode = ( GLFWvidmode * ) glfwGetVideoMode( monitors[i] );

            if ( monitor_vidmode == NULL )
            {
                // Video mode is required for width and height, so skip this monitor
                continue;
            }
            else
            {
                monitor_width  = monitor_vidmode->width;
                monitor_height = monitor_vidmode->height;
            }

            // Set the owner to this monitor if the center of the window is within its bounding box
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
            // Set the window position to the center of the owner monitor
            glfwSetWindowPos( window, owner_x + ( owner_width * 0.5 ) - window_width, owner_y + ( owner_height * 0.5 ) - window_height );
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

    GLFWwindow * Window::GetGLFWWindow()
    {
        return m_Window.get();
    }
}
