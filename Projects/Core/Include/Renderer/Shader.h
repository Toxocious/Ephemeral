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
    class Shader
    {
    public:
        unsigned int ID;

        // Constructor that build the Shader Program from 2 different shaders
        Shader() = default;
        Shader( const char * vertexPath, const char * fragmentPath );

        // Creates a Shader program
        void Create();

        // Activates the Shader Program
        void Activate();

        // Deletes the Shader Program
        void Delete();

        // Utility methods for setting uniforms
        void setBool( const std::string & name, bool value );
        void setInt( const std::string & name, int value );
        void setFloat( const std::string & name, float value );

    private:
        // Reads a text file and outputs a string with everything in the text file
        std::string ReadFile( std::filesystem::path assetPath, std::string filepath );

        // Checks if the different Shaders have compiled properly
        void compileErrors( unsigned int shader, const char * type );

        // Track shader filename
        std::string m_Name;

        // Reference ID of the Shader Program
        uint32_t m_RendererID;

        std::unordered_map<GLenum, std::vector<uint32_t>> m_OpenGLSPIRV;
    };
}

#endif
