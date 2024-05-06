#pragma once

#ifndef EPH_CORE_EBO_H
#    define EPH_CORE_EBO_H

#    include <Core/Ephemeral.h>

namespace Ephemeral
{
    class EBO
    {
    public:
        // ID reference of Elements Buffer Object
        GLuint ID;

        // Constructor that generates a Elements Buffer Object and links it to indices
        EBO() = default;
        EBO( GLuint * indices, GLsizeiptr size );

        // Binds the EBO
        void Bind();
        // Unbinds the EBO
        void Unbind();
        // Deletes the EBO
        void Delete();
    };
}

#endif
