#pragma once

#ifndef EPH_CORE_SHADER_H
#    define EPH_CORE_SHADER_H

#    include <Core/Ephemeral.h>

#    include <cerrno>
#    include <fstream>
#    include <iostream>
#    include <sstream>
#    include <string>

namespace Ephemeral
{
    std::string get_file_contents( const char * filename );

    class Shader
    {
    public:
        // Constructor that build the Shader Program from 2 different shaders
        Shader( std::string folderName, const char * vertexFile, const char * fragmentFile );

        // Activates the Shader Program
        void Activate();
        // Deletes the Shader Program
        void Delete();

    private:
        // Checks if the different Shaders have compiled properly
        void compileErrors( unsigned int shader, const char * type );

        // Reference ID of the Shader Program
        GLuint ID;
    };
}

#endif
