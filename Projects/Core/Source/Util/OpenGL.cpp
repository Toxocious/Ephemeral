#include <Core/Ephemeral.h>

#include <Util/OpenGL.h>

namespace Ephemeral
{
    /**
     * OpenGL Drawing
     */
    void OpenGLUtils::DrawArrays( int n )
    {
        glDrawArrays( GL_TRIANGLES, 0, n );
    }

    void OpenGLUtils::DrawElements( int size )
    {
        glDrawElements( GL_TRIANGLES, size, GL_UNSIGNED_INT, ( void * ) 0 );
    }

    void OpenGLUtils::OldDrawLines( const float3 & begin, const float3 & end )
    {
        // glBegin( GL_LINES );

        // glVertex3f( begin.x, begin.y, begin.z );
        // glVertex3f( end.x, end.y, end.z );

        // glEnd();
    }

    /**
     * OpenGL Buffer Handling
     */
    void OpenGLUtils::BindBuffer( unsigned int id )
    {
        glBindBuffer( GL_ARRAY_BUFFER, id );
    }

    void OpenGLUtils::BindBuffers( unsigned int vao, unsigned int vertex, unsigned int elements )
    {
        glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vertex );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, elements );
    }

    void OpenGLUtils::UnBindBuffers()
    {
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
        glBindVertexArray( 0 );
    }

    void OpenGLUtils::DeleteBuffer( unsigned int & id )
    {
        glDeleteBuffers( 1, &id );
    }

    void OpenGLUtils::BufferSubDataArray( unsigned int size, const void * data )
    {
        glBufferSubData( GL_ARRAY_BUFFER, NULL, size, data );
    }

    void OpenGLUtils::GenVAO( unsigned int & vao )
    {
        glGenVertexArrays( 1, &vao );
        glBindVertexArray( vao );
    }

    void OpenGLUtils::DeleteVAO( unsigned int & vao, unsigned int & vertex, unsigned int & elements )
    {
        glDeleteVertexArrays( 1, &vao );
        glDeleteBuffers( 1, &vertex );
        glDeleteBuffers( 1, &elements );
    }

    void OpenGLUtils::GenArrayBuffer( unsigned int & id, unsigned int size, unsigned int type_size, unsigned int element_size, const float * data )
    {
        glGenBuffers( 1, &id );
        glBindBuffer( GL_ARRAY_BUFFER, id );
        glBufferData( GL_ARRAY_BUFFER, type_size * size * element_size, data, GL_STATIC_DRAW );
    }

    void OpenGLUtils::GenArrayBuffer( unsigned int & id, unsigned int size, unsigned int type_size, unsigned int element_size, const float * data, unsigned int attrib_index, unsigned int attrib_size )
    {
        glGenBuffers( 1, &id );
        glBindBuffer( GL_ARRAY_BUFFER, id );
        glBufferData( GL_ARRAY_BUFFER, type_size * size * element_size, data, GL_STATIC_DRAW );
        // TODO: allow other than GL_FLOAT
        glVertexAttribPointer( attrib_index, attrib_size, GL_FLOAT, GL_FALSE, 0, ( void * ) 0 );
        glEnableVertexAttribArray( attrib_index );
    }

    void OpenGLUtils::SetArrayBuffer( unsigned int & id, unsigned int size, unsigned int type_size, unsigned int element_size, const float * data, unsigned int attrib_index, unsigned int attrib_size )
    {
        glBindBuffer( GL_ARRAY_BUFFER, id );
        glBufferData( GL_ARRAY_BUFFER, type_size * size * element_size, data, GL_STATIC_DRAW );
        // TODO: allow other than GL_FLOAT
        glVertexAttribPointer( attrib_index, attrib_size, GL_FLOAT, GL_FALSE, 0, ( void * ) 0 );
        glEnableVertexAttribArray( attrib_index );
    }

    void OpenGLUtils::GenElementBuffer( unsigned int & id, unsigned int size, const unsigned int * data )
    {
        glGenBuffers( 1, &id );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( unsigned int ) * size, data, GL_STATIC_DRAW );
    }

    /**
     * Texture generation and handling
     */
    void OpenGLUtils::GenTexture( unsigned int & id )
    {
        glGenTextures( 1, &id );
    }

    void OpenGLUtils::ActiveTexture( int val )
    {
        glActiveTexture( GL_TEXTURE0 + val );
    }

    void OpenGLUtils::BindTexture( unsigned int id )
    {
        glBindTexture( GL_TEXTURE_2D, id );
    }

    void OpenGLUtils::UnBindTexture()
    {
        glBindTexture( GL_TEXTURE_2D, 0u );
    }

    void OpenGLUtils::TexSubImage2D( int x, int y, int width, int height, const unsigned char * pixels )
    {
        glTexSubImage2D( GL_TEXTURE_2D, 0, x, y, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels );
    }

    void OpenGLUtils::GenTextureData( unsigned int & id, Wrap wrap, Filter filter, unsigned int size_x, unsigned int size_y, const unsigned char * data )
    {
        glGenTextures( 1, &id );
        glBindTexture( GL_TEXTURE_2D, id );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapEnumToGLEnum( wrap ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapEnumToGLEnum( wrap ) );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterEnumToGLEnum( filter ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterEnumToGLEnum( filter ) );

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB8, size_x, size_y, 0, GL_RGB, GL_UNSIGNED_BYTE, data );

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

        glGenerateMipmap( GL_TEXTURE_2D );
    }

    void OpenGLUtils::SetTextureProperties( unsigned int id, Wrap wrap, Filter filter )
    {
        glBindTexture( GL_TEXTURE_2D, id );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, WrapEnumToGLEnum( wrap ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, WrapEnumToGLEnum( wrap ) );

        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, FilterEnumToGLEnum( filter ) );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, FilterEnumToGLEnum( filter ) );

        glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

        glGenerateMipmap( GL_TEXTURE_2D );
    }

    /**
     * OpenGL Feature enabling/disabling
     */
    void OpenGLUtils::DepthEnable( bool active )
    {
        ( active ) ? glEnable( GL_DEPTH_TEST ) : glDisable( GL_DEPTH_TEST );
    }

    void OpenGLUtils::EnableCullFace( bool active )
    {
        ( active ) ? glEnable( GL_CULL_FACE ) : glDisable( GL_CULL_FACE );
    }

    void OpenGLUtils::PolygonMode( bool line )
    {
        if ( line )
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        }
        else
        {
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        }
    }

    /**
     * Enum utilities
     */
    int OpenGLUtils::WrapEnumToGLEnum( Wrap w )
    {
        switch ( w )
        {
            case OpenGLUtils::ClampToEdge:
                return GL_CLAMP_TO_EDGE;
            case OpenGLUtils::MirroredRepeat:
                return GL_MIRRORED_REPEAT;
            case OpenGLUtils::ClampToBorder:
                return GL_CLAMP_TO_BORDER;
            default:
                return GL_REPEAT;
        }
    }

    int OpenGLUtils::FilterEnumToGLEnum( Filter f )
    {
        if ( f == OpenGLUtils::Nearest )
        {
            return GL_NEAREST;
        }
        else
        {
            return GL_LINEAR;
        }
    }

    /**
     * Status checking and error handling
     */
    void OpenGLUtils::CheckFramebufferStatus()
    {
        GLenum framebufferStatus = glCheckFramebufferStatus( GL_FRAMEBUFFER );
        if ( framebufferStatus != GL_FRAMEBUFFER_COMPLETE )
        {
            switch ( framebufferStatus )
            {
                case GL_FRAMEBUFFER_UNDEFINED:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_UNDEFINED" );
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" );
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" );
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" );
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" );
                    break;
                case GL_FRAMEBUFFER_UNSUPPORTED:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_UNSUPPORTED" );
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" );
                    break;
                case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
                    EPH_CORE_ERROR( "[OpenGLUtils] GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" );
                    break;
                default:
                    EPH_CORE_ERROR( "[OpenGLUtils] Unknown franebuffer status error | {0}", framebufferStatus );
            }
        }
    }

    void OpenGLUtils::_HandleError( const char * func )
    {
        if ( wglGetCurrentContext() == NULL )
        {
            return;
        }

        GLenum err = glGetError();
        while ( err != GL_NO_ERROR )
        {
            std::string error_type;
            switch ( err )
            {
                case GL_INVALID_ENUM:
                    error_type.assign( "GL_INVALID_ENUM" );
                    break;
                case GL_INVALID_VALUE:
                    error_type.assign( "GL_INVALID_VALUE" );
                    break;
                case GL_INVALID_OPERATION:
                    error_type.assign( "GL_INVALID_OPERATION" );
                    break;
                case GL_INVALID_FRAMEBUFFER_OPERATION:
                    error_type.assign( "GL_INVALID_FRAMEBUFFER_OPERATION" );
                    break;
                case GL_OUT_OF_MEMORY:
                    error_type.assign( "GL_OUT_OF_MEMORY" );
                    break;
                case GL_STACK_UNDERFLOW:
                    error_type.assign( "GL_STACK_UNDERFLOW" );
                    break;
                case GL_STACK_OVERFLOW:
                    error_type.assign( "GL_STACK_OVERFLOW" );
                    break;
                default:
                    break;
            }

            EPH_CORE_ERROR( "OpenGL error {0} ({1}) on {2}", err, error_type.c_str(), func );
            err = glGetError();
        }
    }

    /**
     * Misc.
     */
    std::string OpenGLUtils::GetVendor()
    {
        return std::string( ( const char * ) glGetString( GL_VENDOR ) );
    }

    std::string OpenGLUtils::GetModel()
    {
        return std::string( ( const char * ) glGetString( GL_RENDERER ) );
    }

    std::string OpenGLUtils::GetVersion()
    {
        return std::string( ( const char * ) glGetString( GL_VERSION ) );
    }
}
