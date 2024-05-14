#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Renderer/Viewport.h>

namespace Ephemeral
{
    Viewport::Viewport()
    {
        EPH_CORE_TRACE( "Viewport constructed." );

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
        // camera->UpdateFrustum( x, y );
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
        // App->camera->UpdateShaders( camera );
        glViewport( 0, 0, m_Size.x, m_Size.y );
    }

    void Viewport::End() const
    {
        glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    }

    void Viewport::RenderOnImGui()
    {
        // camera->is_active = ImGui::IsWindowHovered();
    }

    void Viewport::DrawGrid()
    {
        Begin();

        static auto gridShader = App->m_Renderer->GetShader( "Grid" );
        gridShader->Use();

        // OpenGLUtil::DepthEnable( true );
        // OpenGLUtil::DrawArrays( 6 );
        // OpenGLUtil::DepthEnable( false );

        End();
    }
}
