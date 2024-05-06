#pragma once

#ifndef EPH_CORE_VAO_H
#    define EPH_CORE_VAO_H

#    include <Core/Ephemeral.h>
#    include <Renderer/VertexBufferObject.h>

namespace Ephemeral
{
    class VAO
    {
    public:
        // ID reference for the Vertex Array Object
        GLuint ID;

        // Constructor that generates a VAO ID
        VAO( int t );
        VAO() = default;

        // Links a VBO Attribute such as a position or color to the VAO
        void LinkAttrib( VBO & VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void * offset );
        // Binds the VAO
        void Bind();
        // Unbinds the VAO
        void Unbind();
        // Deletes the VAO
        void Delete();
    };
}

#endif
