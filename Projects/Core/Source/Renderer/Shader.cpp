#pragma once

#include <Core/Ephemeral.h>

#include <Renderer/Shader.h>

namespace Ephemeral
{
    // Reads a text file and outputs a string with everything in the text file
    std::string get_file_contents( const char * filename )
    {
        std::ifstream in( filename, std::ios::binary );
        if ( in )
        {
            std::string contents;
            in.seekg( 0, std::ios::end );
            contents.resize( in.tellg() );
            in.seekg( 0, std::ios::beg );
            in.read( &contents[0], contents.size() );
            in.close();
            return contents;
        }
        throw( errno );
    }

    // Constructor that build the Shader Program from 2 different shaders
    Shader::Shader( std::string folderName, const char * vertexFile, const char * fragmentFile )
    {
        EPH_CORE_TRACE( "Attempting to initialize shaders" );
        {
            namespace fs = std::filesystem;

            std::vector<std::string> shaderFiles;

            // Get the directory path of the current source file
            std::filesystem::path currentSourcePath( __FILE__ );
            std::filesystem::path shaderDirectory = currentSourcePath.parent_path().parent_path().parent_path().concat( "\\Assets\\Shaders" ).concat( "\\" + folderName );

            // Check if the directory exists
            if ( !std::filesystem::exists( shaderDirectory ) )
            {
                EPH_CORE_WARN( "Couldn't find directory for the '{0]' shader.", folderName );
                return;
            }

            // Iterate over the directory contents
            for ( const auto & entry : std::filesystem::directory_iterator( shaderDirectory ) )
            {
                if ( entry.is_regular_file() )
                {
                    // Check if the file has a ".glsl" extension (you can adjust this as needed)
                    if ( entry.path().extension() == ".frag" || entry.path().extension() == ".vert" )
                    {
                        shaderFiles.push_back( entry.path().string() );
                    }
                }
            }

            for ( const auto & filePath : shaderFiles )
            {
                EPH_CORE_INFO( "Loaded '{0}' shader file", filePath );

                std::ifstream     file( filePath );
                std::stringstream buffer;
                buffer << file.rdbuf();

                // Process the shader source code as needed
                // For example, compile the shader if it's not already compiled
                // std::cout << "Shader Source:" << std::endl;
                // std::cout << buffer.str() << std::endl;
            }
        }

        return;

        // Read vertexFile and fragmentFile and store the strings
        std::string vertexCode   = get_file_contents( vertexFile );
        std::string fragmentCode = get_file_contents( fragmentFile );

        // Convert the shader source strings into character arrays
        const char * vertexSource   = vertexCode.c_str();
        const char * fragmentSource = fragmentCode.c_str();

        // Create Vertex Shader Object and get its reference
        GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );
        // Attach Vertex Shader source to the Vertex Shader Object
        glShaderSource( vertexShader, 1, &vertexSource, NULL );
        // Compile the Vertex Shader into machine code
        glCompileShader( vertexShader );
        // Checks if Shader compiled succesfully
        compileErrors( vertexShader, "VERTEX" );

        // Create Fragment Shader Object and get its reference
        GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
        // Attach Fragment Shader source to the Fragment Shader Object
        glShaderSource( fragmentShader, 1, &fragmentSource, NULL );
        // Compile the Vertex Shader into machine code
        glCompileShader( fragmentShader );
        // Checks if Shader compiled succesfully
        compileErrors( fragmentShader, "FRAGMENT" );

        // Create Shader Program Object and get its reference
        ID = glCreateProgram();
        // Attach the Vertex and Fragment Shaders to the Shader Program
        glAttachShader( ID, vertexShader );
        glAttachShader( ID, fragmentShader );
        // Wrap-up/Link all the shaders together into the Shader Program
        glLinkProgram( ID );
        // Checks if Shaders linked succesfully
        compileErrors( ID, "PROGRAM" );

        // Delete the now useless Vertex and Fragment Shader objects
        glDeleteShader( vertexShader );
        glDeleteShader( fragmentShader );
    }

    // Activates the Shader Program
    void Shader::Activate()
    {
        glUseProgram( ID );
    }

    // Deletes the Shader Program
    void Shader::Delete()
    {
        glDeleteProgram( ID );
    }

    // Checks if the different Shaders have compiled properly
    void Shader::compileErrors( unsigned int shader, const char * type )
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
                // std::cout << "SHADER_COMPILATION_ERROR for:" << type << "\n"
                //           << infoLog << std::endl;

                EPH_CORE_ERROR( "Shader compilation failed - {0} {1}", type, infoLog );
            }
        }
        else
        {
            glGetProgramiv( shader, GL_LINK_STATUS, &hasCompiled );
            if ( hasCompiled == GL_FALSE )
            {
                glGetProgramInfoLog( shader, 1024, NULL, infoLog );
                // std::cout << "SHADER_LINKING_ERROR for:" << type << "\n"
                //           << infoLog << std::endl;

                EPH_CORE_ERROR( "Shader linking failed - {0} {1}", type, infoLog );
            }
        }
    }
}
