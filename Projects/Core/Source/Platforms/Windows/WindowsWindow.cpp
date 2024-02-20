// #include "Ephemeral/Renderer/Renderer.h"

#include <Core/Window.h>

#include <Platforms/OpenGL/OpenGLContext.h>
#include <Platforms/Windows/WindowsWindow.h>

#include <Events/AppEvent.h>
#include <Events/Input.h>
#include <Events/KeyEvent.h>
#include <Events/MouseEvent.h>

#include <Util/Base.h>
#include <Util/Profile.h>

namespace Ephemeral
{
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback( int error, const char * description )
    {
        EPH_CORE_ERROR( "GLFW Error ({0}): {1}", error, description );
    }

    WindowsWindow::WindowsWindow( const WindowProps & props )
    {
        EPH_PROFILE_FUNCTION();

        Init( props );
    }

    WindowsWindow::~WindowsWindow()
    {
        EPH_PROFILE_FUNCTION();

        Shutdown();
    }

    void WindowsWindow::Init( const WindowProps & props )
    {
        EPH_PROFILE_FUNCTION();

        m_Data.Title  = props.Title;
        m_Data.Width  = props.Width;
        m_Data.Height = props.Height;

        EPH_CORE_INFO( "Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height );

        if ( s_GLFWWindowCount == 0 )
        {
            EPH_PROFILE_SCOPE( "glfwInit" );

            int success = glfwInit();
            if ( !success ) {
                EPH_CORE_CRITICAL( "Failed to initialize GLFW." );
                EPH_CORE_ASSERT( success, "Could not initialize GLFW!" );
            }
            glfwSetErrorCallback( GLFWErrorCallback );
        }

        EPH_CORE_INFO("GLFW successfully initialized");

        {
            EPH_PROFILE_SCOPE( "glfwCreateWindow" );

            EPH_CORE_INFO( "Creating GLFW window." );
            m_Window = glfwCreateWindow( ( int ) props.Width, ( int ) props.Height, m_Data.Title.c_str(), nullptr, nullptr );
            ++s_GLFWWindowCount;

            if ( m_Window == nullptr )
                EPH_CORE_CRITICAL("Failed to create GLFW window.");
        }

        m_Context = GraphicsContext::Create( m_Window );
        m_Context->Init();

        glfwSetWindowUserPointer( m_Window, &m_Data );
        SetVSync( true );

        // Set GLFW callbacks
        glfwSetWindowSizeCallback( m_Window, []( GLFWwindow * window, int width, int height )
                                   {
                                       WindowData & data = *( WindowData * ) glfwGetWindowUserPointer( window );
                                       data.Width        = width;
                                       data.Height       = height;

                                       WindowResizeEvent event( width, height );
                                       data.EventCallback( event );
                                   } );

        glfwSetWindowCloseCallback( m_Window, []( GLFWwindow * window )
                                    {
                                        WindowData &     data = *( WindowData * ) glfwGetWindowUserPointer( window );
                                        WindowCloseEvent event;
                                        data.EventCallback( event );
                                    } );

        glfwSetKeyCallback( m_Window, []( GLFWwindow * window, int key, int scancode, int action, int mods )
                            {
                                WindowData & data = *( WindowData * ) glfwGetWindowUserPointer( window );

                                switch ( action )
                                {
                                    case GLFW_PRESS:
                                        {
                                            KeyPressedEvent event( key, 0 );
                                            data.EventCallback( event );
                                            break;
                                        }
                                    case GLFW_RELEASE:
                                        {
                                            KeyReleasedEvent event( key );
                                            data.EventCallback( event );
                                            break;
                                        }
                                    case GLFW_REPEAT:
                                        {
                                            KeyPressedEvent event( key, true );
                                            data.EventCallback( event );
                                            break;
                                        }
                                }
                            } );

        glfwSetCharCallback( m_Window, []( GLFWwindow * window, unsigned int keycode )
                             {
                                 WindowData & data = *( WindowData * ) glfwGetWindowUserPointer( window );

                                 KeyTypedEvent event( keycode );
                                 data.EventCallback( event );
                             } );

        glfwSetMouseButtonCallback( m_Window, []( GLFWwindow * window, int button, int action, int mods )
                                    {
                                        WindowData & data = *( WindowData * ) glfwGetWindowUserPointer( window );

                                        switch ( action )
                                        {
                                            case GLFW_PRESS:
                                                {
                                                    MouseButtonPressedEvent event( button );
                                                    data.EventCallback( event );
                                                    break;
                                                }
                                            case GLFW_RELEASE:
                                                {
                                                    MouseButtonReleasedEvent event( button );
                                                    data.EventCallback( event );
                                                    break;
                                                }
                                        }
                                    } );

        glfwSetScrollCallback( m_Window, []( GLFWwindow * window, double xOffset, double yOffset )
                               {
                                   WindowData & data = *( WindowData * ) glfwGetWindowUserPointer( window );

                                   MouseScrolledEvent event( ( float ) xOffset, ( float ) yOffset );
                                   data.EventCallback( event );
                               } );

        glfwSetCursorPosCallback( m_Window, []( GLFWwindow * window, double xPos, double yPos )
                                  {
                                      WindowData & data = *( WindowData * ) glfwGetWindowUserPointer( window );

                                      MouseMovedEvent event( ( float ) xPos, ( float ) yPos );
                                      data.EventCallback( event );
                                  } );
    }

    void WindowsWindow::Shutdown()
    {
        EPH_PROFILE_FUNCTION();

        glfwDestroyWindow( m_Window );
        --s_GLFWWindowCount;

        if ( s_GLFWWindowCount == 0 )
        {
            glfwTerminate();
        }
    }

    void WindowsWindow::OnUpdate()
    {
        EPH_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    void WindowsWindow::SetVSync( bool enabled )
    {
        EPH_PROFILE_FUNCTION();

        if ( enabled )
        {
            glfwSwapInterval( 1 );
        }
        else
        {
            glfwSwapInterval( 0 );
        }

        m_Data.VSync = enabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_Data.VSync;
    }
}
