#include <Core/Ephemeral.h>

#include <Util/Window.h>

#include <Renderer/Imgui.h>

#include <Renderer/Shader.h>

#include <Renderer/ElementBufferObject.h>
#include <Renderer/VertexArrayObject.h>
#include <Renderer/VertexBufferObject.h>

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

        glViewport( 0, 0, m_Width, m_Height );

        EPH_CORE_TRACE( "Successfully initialized GLFW and GLAD, and created a window." );

        CompileShaders();

        Ephemeral::Imgui::Initialize( m_Window.get() );
    }

    Window::~Window()
    {
        Ephemeral::Imgui::Shutdown();

        // Clean up resources
        glDeleteVertexArrays( 1, &VAO );
        glDeleteBuffers( 1, &VBO );
        m_ShaderProgram.Delete();

        // Terminate GLFW
        glfwDestroyWindow( m_Window.get() );
        glfwTerminate();
    }

    void Window::Run()
    {
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

                // Use the shader program
                m_ShaderProgram.Activate();

                // Bind the VAO
                glBindVertexArray( VAO );

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

    void Window::CompileShaders()
    {
        Ephemeral::Shader m_ShaderProgram( "default.vert", "default.frag" );

        float vertices[] = {
            // positions         // colors
            0.5f,
            -0.5f,
            0.0f,
            1.0f,
            0.0f,
            0.0f, // bottom right
            -0.5f,
            -0.5f,
            0.0f,
            0.0f,
            1.0f,
            0.0f, // bottom left
            0.0f,
            0.5f,
            0.0f,
            0.0f,
            0.0f,
            1.0f // top
        };

        Ephemeral::VAO VAO;
        Ephemeral::VBO VBO( vertices, sizeof( vertices ) );
        // Ephemeral::EBO EBO(indices, sizeof(indices));

        VAO.Bind();
        VBO.Bind();
        // EBO.Bind();

        VAO.LinkAttrib( VBO, 0, 3, GL_FLOAT, 6 * sizeof( float ), ( void * ) 0 );
        VAO.LinkAttrib( VBO, 1, 3, GL_FLOAT, 6 * sizeof( float ), ( void * ) ( 3 * sizeof( float ) ) );
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
