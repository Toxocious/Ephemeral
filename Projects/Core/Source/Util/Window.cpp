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

        glViewport( 0, 0, m_Width, m_Height );

        EPH_CORE_TRACE( "Successfully initialized GLFW and GLAD, and created a window." );

        CompileShaders();

        Ephemeral::Imgui::Initialize( m_Window.get() );
    }

    Window::~Window()
    {
        Ephemeral::Imgui::Shutdown();

        // Clean up resources
        m_VAO.Delete();
        m_VBO.Delete();

        // glDeleteVertexArrays( 1, &m_VAO );
        // glDeleteBuffers( 1, &m_VBO );
        m_ShaderProgram.Delete();

        // Terminate GLFW
        glfwDestroyWindow( m_Window.get() );
        glfwTerminate();
    }

    void Window::Run()
    {
        // Gets ID of uniform called "scale"
        GLuint uniID = glGetUniformLocation( m_ShaderProgram.ID, "scale" );

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

                glUniform1f( uniID, 0.5f );

                // Bind the VAO
                // glBindVertexArray( m_VAO );
                m_VAO.Bind();

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

        // Vertices coordinates
        GLfloat vertices[] = {
            //               COORDINATES                  /     COLORS           //
            -0.5f,
            -0.5f * float( sqrt( 3 ) ) * 1 / 3,
            0.0f,
            0.8f,
            0.3f,
            0.02f, // Lower left corner
            0.5f,
            -0.5f * float( sqrt( 3 ) ) * 1 / 3,
            0.0f,
            0.8f,
            0.3f,
            0.02f, // Lower right corner
            0.0f,
            0.5f * float( sqrt( 3 ) ) * 2 / 3,
            0.0f,
            1.0f,
            0.6f,
            0.32f, // Upper corner
            -0.25f,
            0.5f * float( sqrt( 3 ) ) * 1 / 6,
            0.0f,
            0.9f,
            0.45f,
            0.17f, // Inner left
            0.25f,
            0.5f * float( sqrt( 3 ) ) * 1 / 6,
            0.0f,
            0.9f,
            0.45f,
            0.17f, // Inner right
            0.0f,
            -0.5f * float( sqrt( 3 ) ) * 1 / 3,
            0.0f,
            0.8f,
            0.3f,
            0.02f // Inner down
        };

        // Indices for vertices order
        GLuint indices[] = {
            0,
            3,
            5, // Lower left triangle
            3,
            2,
            4, // Lower right triangle
            5,
            4,
            1 // Upper triangle
        };

        Ephemeral::VAO m_VAO;
        Ephemeral::VBO m_VBO( vertices, sizeof( vertices ) );
        // Ephemeral::EBO m_EBO(indices, sizeof(indices));

        m_VAO.Bind();
        m_VBO.Bind();
        // m_EBO.Bind();

        m_VAO.LinkAttrib( m_VBO, 0, 3, GL_FLOAT, 6 * sizeof( float ), ( void * ) 0 );
        m_VAO.LinkAttrib( m_VBO, 1, 3, GL_FLOAT, 6 * sizeof( float ), ( void * ) ( 3 * sizeof( float ) ) );
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
