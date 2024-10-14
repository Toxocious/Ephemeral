#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Renderer/Viewport.h>

#include <Util/OpenGL.h>

#include <glm/gtc/type_ptr.hpp>

namespace Ephemeral
{
    Viewport::Viewport( const char * name )
        : m_Name( name )
    {
        EPH_CORE_INFO( "Viewport '{0}' constructed.", name );

        glGenFramebuffers( 1, &m_ID[FBO_MS] );
        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO_MS] );

        // generate texture
        glGenTextures( 1, &m_ID[TEXTURE_MS] );
        glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, m_ID[TEXTURE_MS] );
        glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA, 1, 1, GL_TRUE );
        glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, 0 );

        // attach it to currently bound framebuffer object
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ID[TEXTURE_MS], 0 );

        glGenRenderbuffers( 1, &m_ID[RBO_MS] );
        glBindRenderbuffer( GL_RENDERBUFFER, m_ID[RBO_MS] );
        glRenderbufferStorageMultisample( GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, 1, 1 );
        glBindRenderbuffer( GL_RENDERBUFFER, 0 );

        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID[RBO_MS] );

        //========================================================================

        glGenFramebuffers( 1, &m_ID[FBO] );
        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO] );

        // generate texture
        glGenTextures( 1, &m_ID[TEXTURE] );
        glBindTexture( GL_TEXTURE_2D, m_ID[TEXTURE] );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glBindTexture( GL_TEXTURE_2D, 0 );

        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ID[TEXTURE], 0 );

        glGenRenderbuffers( 1, &m_ID[RBO] );
        glBindRenderbuffer( GL_RENDERBUFFER, m_ID[RBO] );
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1, 1 );
        glBindRenderbuffer( GL_RENDERBUFFER, 0 );

        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID[RBO] );

        // Handle OpenGL errors below?
    }

    Viewport::~Viewport()
    {
    }

    void Viewport::Clear()
    {
        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO_MS] );
        glClearColor( m_Color[0], m_Color[1], m_Color[2], 1.0f );
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }

    void Viewport::Update()
    {
        // =========================================
        //=== Update tex
        // TODO: Update Camera FOV
        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO_MS] );

        glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, m_ID[TEXTURE_MS] );
        glTexImage2DMultisample( GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, m_Size.x, m_Size.y, GL_TRUE );
        glBindTexture( GL_TEXTURE_2D_MULTISAMPLE, 0 );

        // attach it to currently bound framebuffer object
        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_ID[TEXTURE_MS], 0 );

        glBindRenderbuffer( GL_RENDERBUFFER, m_ID[RBO_MS] );
        glRenderbufferStorageMultisample( GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y );
        glBindRenderbuffer( GL_RENDERBUFFER, 0 );

        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID[RBO_MS] );

        //========================================================================

        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO] );

        // generate texture
        glBindTexture( GL_TEXTURE_2D, m_ID[TEXTURE] );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, m_Size.x, m_Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0 );
        glBindTexture( GL_TEXTURE_2D, 0 );

        glFramebufferTexture2D( GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ID[TEXTURE], 0 );

        glBindRenderbuffer( GL_RENDERBUFFER, m_ID[RBO] );
        glRenderbufferStorage( GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Size.x, m_Size.y );
        glBindRenderbuffer( GL_RENDERBUFFER, 0 );

        glFramebufferRenderbuffer( GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_ID[RBO] );

        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO_MS] );
    }

    void Viewport::UpdateSize( int x, int y )
    {
        m_Size = { x, y };
        m_Camera->UpdateFrustum( x, y );
    }

    void Viewport::Blit() const
    {
        glBindFramebuffer( GL_READ_FRAMEBUFFER, m_ID[FBO_MS] );
        glBindFramebuffer( GL_DRAW_FRAMEBUFFER, m_ID[FBO] );
        glBlitFramebuffer( 0, 0, m_Size.x, m_Size.y, 0, 0, m_Size.x, m_Size.y, GL_COLOR_BUFFER_BIT, GL_NEAREST );

        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    }

    unsigned int Viewport::GetTexture() const
    {
        return m_ID[TEXTURE];
    }

    void Viewport::Begin() const
    {
        glBindFramebuffer( GL_FRAMEBUFFER, m_ID[FBO_MS] );
        App->m_SceneCamera->UpdateShaders( m_Camera );
        glViewport( 0, 0, m_Size.x, m_Size.y );
    }

    void Viewport::End() const
    {
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    }

    void Viewport::RenderOnImGui()
    {
    }

    void Viewport::DrawGrid()
    {
        Begin();

        {
            static auto gridShader = App->m_Renderer->GetShader( "Grid" );
            gridShader->Use();

            OpenGLUtils::DepthEnable( true );
            OpenGLUtils::DrawArrays( 6 );
            OpenGLUtils::DepthEnable( false );
        }

        End();

        {
            DrawTriangle();
        }
    }

    void Viewport::DrawTriangle()
    {
        Begin();

        // static auto triangleShader = App->m_Renderer->GetShader( "Triangle" );
        static auto triangleShader = App->m_Renderer->GetShader( "Triangle" );
        triangleShader->Use();

        // Vertex data for a simple triangle (position only)
        // Vertex data for a plane (2 triangles forming a square)
        static float planeVertices[] = {
            // Positions          // Texture Coords (optional)
            0.5f,
            0.5f,
            0.0f, // Top Right
            0.5f,
            -0.5f,
            0.0f, // Bottom Right
            -0.5f,
            -0.5f,
            0.0f, // Bottom Left
            -0.5f,
            0.5f,
            0.0f // Top Left
        };

        // Indices to form two triangles for the square
        static unsigned int planeIndices[] = {
            0,
            1,
            3, // First triangle (Top Right, Bottom Right, Top Left)
            1,
            2,
            3 // Second triangle (Bottom Right, Bottom Left, Top Left)
        };

        // Step 1: Create and bind a Vertex Array Object (VAO)
        unsigned int VAO;
        glGenVertexArrays( 1, &VAO );
        glBindVertexArray( VAO );

        // Step 2: Create a Vertex Buffer Object (VBO) and copy the vertex data into it
        unsigned int VBO;
        glGenBuffers( 1, &VBO );
        glBindBuffer( GL_ARRAY_BUFFER, VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( planeVertices ), planeVertices, GL_STATIC_DRAW );

        // Step 3: Create an Element Buffer Object (EBO) for the indices
        unsigned int EBO;
        glGenBuffers( 1, &EBO );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( planeIndices ), planeIndices, GL_STATIC_DRAW );

        // Step 4: Define the vertex attributes (positions in this case)
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof( float ), ( void * ) 0 );
        glEnableVertexAttribArray( 0 );

        // Retrieve view and projection matrices from the camera
        auto view       = m_Camera->frustum.ViewMatrix();       // Assuming m_Camera has getViewMatrix()
        auto projection = m_Camera->frustum.ProjectionMatrix(); // Assuming m_Camera has getProjectionMatrix()

        // Pass the view and projection matrices to the shader
        int viewLoc = glGetUniformLocation( triangleShader->GetID(), "view" );
        int projLoc = glGetUniformLocation( triangleShader->GetID(), "projection" );

        triangleShader->SetMat4( "view", view );
        triangleShader->SetMat4( "projection", projection );

        // Step 5: Draw the plane (bind VAO and call glDrawElements)
        glBindVertexArray( VAO );
        glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
        glBindVertexArray( 0 );

        // Optional: Cleanup (delete VBO, EBO, and VAO after use)
        glDeleteBuffers( 1, &VBO );
        glDeleteBuffers( 1, &EBO );
        glDeleteVertexArrays( 1, &VAO );

        End();
    }
}
