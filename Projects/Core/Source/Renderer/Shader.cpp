#pragma once

#include <Core/Ephemeral.h>

#include <Renderer/Shader.h>

namespace Ephemeral
{
    // Constructor that build the Shader Program from 2 different shaders
    Shader::Shader( const char * vertexFile, const char * fragmentFile )
    {
        EPH_CORE_TRACE( "Attempting to initialize shaders - '{0}' '{1}", vertexFile, fragmentFile );
        {
            std::string vertexCode   = ReadFile( Ephemeral::Global::GetCoreAssetPath(), "\\Shaders\\Default\\default.vert" );
            std::string fragmentCode = ReadFile( Ephemeral::Global::GetCoreAssetPath(), "\\Shaders\\Default\\default.frag" );

            const char * vShaderCode = vertexCode.c_str();
            const char * fShaderCode = fragmentCode.c_str();

            unsigned int vertex, fragment;

            vertex = glCreateShader( GL_VERTEX_SHADER );
            glShaderSource( vertex, 1, &vShaderCode, NULL );
            glCompileShader( vertex );
            CheckCompilationErrors( vertex, "VERTEX" );

            fragment = glCreateShader( GL_FRAGMENT_SHADER );
            glShaderSource( fragment, 1, &fShaderCode, NULL );
            glCompileShader( fragment );
            CheckCompilationErrors( fragment, "FRAGMENT" );

            ID = glCreateProgram();
            glAttachShader( ID, vertex );
            glAttachShader( ID, fragment );
            glLinkProgram( ID );
            CheckCompilationErrors( ID, "PROGRAM" );

            glDeleteShader( vertex );
            glDeleteShader( fragment );
        }
        EPH_CORE_TRACE( "Shaders successfully initialized." );
    }

    // Activates the Shader Program
    void Shader::Activate()
    {
        glUseProgram( m_RendererID );
    }

    // Deletes the Shader Program
    void Shader::Delete()
    {
        glDeleteProgram( m_RendererID );
    }

    void Shader::setBool( const std::string & name, bool value )
    {
        glUniform1i( glGetUniformLocation( ID, name.c_str() ), ( int ) value );
    }

    void Shader::setInt( const std::string & name, int value )
    {
        glUniform1i( glGetUniformLocation( ID, name.c_str() ), value );
    }

    void Shader::setFloat( const std::string & name, float value )
    {
        glUniform1f( glGetUniformLocation( ID, name.c_str() ), value );
    }

    // Reads a text file and outputs a string with everything in the text file
    std::string Shader::ReadFile( std::filesystem::path assetPath, std::string filepath )
    {
        std::string fullPath = assetPath.string().append( filepath );

        std::string   result;
        std::ifstream in( fullPath, std::ios::in | std::ios::binary );
        if ( in )
        {
            in.seekg( 0, std::ios::end );
            size_t size = in.tellg();
            if ( size != -1 )
            {
                result.resize( size );
                in.seekg( 0, std::ios::beg );
                in.read( &result[0], size );
            }
            else
            {
                EPH_CORE_ERROR( "Could not read from file '{0}'", fullPath );
                return nullptr;
            }
        }
        else
        {
            EPH_CORE_ERROR( "Could not open file '{0}'", fullPath );
            return nullptr;
        }

        return result;
    }

    // Checks if the different Shaders have compiled properly
    void Shader::CheckCompilationErrors( unsigned int shader, const char * type )
    {
        // Stores status of compilation
        GLint hasCompiled;

        // Character array to store error message in
        char infoLog[1024];
        if ( type != "PROGRAM" )
        {
            glGetShaderiv( shader, GL_COMPILE_STATUS, &hasCompiled );
            if ( hasCompiled == GL_FALSE )
            {
                glGetShaderInfoLog( shader, 1024, NULL, infoLog );

                EPH_CORE_ERROR( "Shader compilation failed - {0} {1}", type, infoLog );
            }
        }
        else
        {
            glGetProgramiv( shader, GL_LINK_STATUS, &hasCompiled );
            if ( hasCompiled == GL_FALSE )
            {
                glGetProgramInfoLog( shader, 1024, NULL, infoLog );

                EPH_CORE_ERROR( "Shader linking failed - {0} {1}", type, infoLog );
            }
        }
    }
}
