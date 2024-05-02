#pragma once

#ifndef EPH_CORE_VBO_H
#    define EPH_CORE_VBO_H

#    include <Core/Ephemeral.h>

namespace Ephemeral
{
    class VBO
    {
    public:
        // Reference ID of the Vertex Buffer Object
        GLuint ID;
        // Constructor that generates a Vertex Buffer Object and links it to vertices
        VBO( GLfloat * vertices, GLsizeiptr size );

        // Binds the VBO
        void Bind();
        // Unbinds the VBO
        void Unbind();
        // Deletes the VBO
        void Delete();

    private:
        GLfloat *  m_Vertices;
        GLsizeiptr m_Size;
    };
}
#endif
