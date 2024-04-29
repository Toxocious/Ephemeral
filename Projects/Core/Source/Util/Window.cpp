#include <Core/Ephemeral.h>

#include <Util/Window.h>

#include <Renderer/Imgui.h>
#include <Renderer/Shader.h>

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
        glDeleteProgram( m_ShaderProgram );

        // Terminate GLFW
        glfwDestroyWindow( m_Window.get() );
        glfwTerminate();
    }

    void Window::Run()
    {
        // Main loop
        while ( !ShouldClose() )
        {
            // Check and call events
            PollEvents();

            {
                // Clear the colorbuffer
                glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );
                glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

                Ephemeral::Imgui::NewFrame();

                // Enable depth testing
                glEnable( GL_DEPTH_TEST );

                // Use the shader program
                glUseProgram( m_ShaderProgram );

                // Bind the VAO
                glBindVertexArray( VAO );

                // Draw the triangle
                glDrawArrays( GL_TRIANGLES, 0, 3 );

                {
                    Ephemeral::Imgui::RenderFps();
                }

                // Unbind the VAO
                glBindVertexArray( 0 );
            }

            Ephemeral::Imgui::RenderFrame();

            // Swap the screen buffers
            SwapBuffers();
        }
    }

    void Window::CompileShaders()
    {
        Ephemeral::Shader shaderProgram( "Default", "default.vert", "default.frag" );
    }

    // void Window::CompileShaders()
    // {
    //     EPH_CORE_TRACE( "Compiling shaders" );

    //     const GLchar * vertexShaderSource = "#version 330 core\n"
    //                                         "layout (location = 0) in vec3 aPos;\n"
    //                                         "uniform float size;\n"
    //                                         "void main()\n"
    //                                         "{\n"
    //                                         "   gl_Position = vec4(size * aPos.x, size * aPos.y, size * aPos.z, 1.0);\n"
    //                                         "}\0";

    //     const GLchar * fragmentShaderSource = "#version 330 core\n"
    //                                           "out vec4 FragColor;\n"
    //                                           "uniform vec4 color;\n"
    //                                           "void main()\n"
    //                                           "{\n"
    //                                           "   FragColor = color;\n"
    //                                           "}\n\0";

    //     // Create Vertex Shader Object and get its reference
    //     GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
    //     // Attach Vertex Shader source to the Vertex Shader Object
    //     glShaderSource( vertexShader, 1, &vertexShaderSource, NULL );
    //     // Compile the Vertex Shader into machine code
    //     glCompileShader( vertexShader );

    //     // Create Fragment Shader Object and get its reference
    //     GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    //     // Attach Fragment Shader source to the Fragment Shader Object
    //     glShaderSource( fragmentShader, 1, &fragmentShaderSource, NULL );
    //     // Compile the Vertex Shader into machine code
    //     glCompileShader( fragmentShader );

    //     // Create Shader Program Object and get its reference
    //     GLuint shaderProgram = glCreateProgram();
    //     // Attach the Vertex and Fragment Shaders to the Shader Program
    //     glAttachShader( shaderProgram, vertexShader );
    //     glAttachShader( shaderProgram, fragmentShader );
    //     // Wrap-up/Link all the shaders together into the Shader Program
    //     glLinkProgram( shaderProgram );

    //     // Delete the now useless Vertex and Fragment Shader objects
    //     glDeleteShader( vertexShader );
    //     glDeleteShader( fragmentShader );

    //     // Vertices coordinates
    //     GLfloat vertices[] = {
    //         -0.5f,
    //         -0.5f * float( sqrt( 3 ) ) / 3,
    //         0.0f, // Lower left corner
    //         0.5f,
    //         -0.5f * float( sqrt( 3 ) ) / 3,
    //         0.0f, // Lower right corner
    //         0.0f,
    //         0.5f * float( sqrt( 3 ) ) * 2 / 3,
    //         0.0f // Upper corner
    //     };

    //     // Create Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
    //     glGenVertexArrays( 1, &VAO );
    //     glGenBuffers( 1, &VBO );

    //     // Bind VAO first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //     glBindVertexArray( VAO );

    //     glBindBuffer( GL_ARRAY_BUFFER, VBO );
    //     glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    //     // Position attribute
    //     glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( GLfloat ), ( GLvoid * ) 0 );
    //     glEnableVertexAttribArray( 0 );

    //     // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
    //     glBindBuffer( GL_ARRAY_BUFFER, 0 );
    //     glBindVertexArray( 0 );
    //     glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );

    //     EPH_CORE_TRACE( "Shaders have finished compiling" );
    // }

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
