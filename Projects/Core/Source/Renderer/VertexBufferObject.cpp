#include <Core/Ephemeral.h>
#include <Renderer/VertexBufferObject.h>

namespace Ephemeral
{
    // Constructor that generates a Vertex Buffer Object and links it to vertices
    VBO::VBO( GLfloat * vertices, GLsizeiptr size )
        : m_Vertices( vertices ), m_Size( size )
    {
        glGenBuffers( 1, &ID );
    }

    // Binds the VBO
    void VBO::Bind()
    {
        glBindBuffer( GL_ARRAY_BUFFER, ID );
        glBufferData( GL_ARRAY_BUFFER, m_Size, m_Vertices, GL_STATIC_DRAW );
    }

    // Unbinds the VBO
    void VBO::Unbind()
    {
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
    }

    // Deletes the VBO
    void VBO::Delete()
    {
        glDeleteBuffers( 1, &ID );
    }
}
