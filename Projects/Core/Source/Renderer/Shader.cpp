#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Renderer/Shader.h>

#include <Util/FileSystem.h>

namespace Ephemeral
{
    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
    }

    /**
     * Tell OpenGL to use the Shader program.
     */
    void Shader::Use()
    {
        glUseProgram( m_ID );
    }

    /**
     * Creates a program, attaches the shaders, and links the program.
     */
    void Shader::Link( unsigned int vertex, unsigned int fragment )
    {
        m_ID = glCreateProgram();

        glAttachShader( m_ID, vertex );
        glAttachShader( m_ID, fragment );

        glLinkProgram( m_ID );

        CheckCompileErrors( m_ID, ShaderType::PROGRAM );
    }

    /**
     * Compiles a GLSL shader given a filepath.
     */
    unsigned int Shader::Compile( const std::string & filepath )
    {
        unsigned int shaderCreated = 0;

        std::string shaderSource;

        try
        {
            shaderSource = FileSystem::OpenTextFile( filepath.c_str() );
        }
        catch ( const char * exception )
        {
            EPH_CORE_ERROR( "Failed to read shader '{0]' - {1]", filepath, exception );

            return shaderCreated;
        }

        const char * shaderCode = shaderSource.c_str();

        if ( filepath.find( ".vertex.glsl" ) != std::string::npos )
        {
            shaderCreated = glCreateShader( GL_VERTEX_SHADER );
            glShaderSource( shaderCreated, 1, &shaderCode, NULL );
            glCompileShader( shaderCreated );
            CheckCompileErrors( shaderCreated, ShaderType::VERTEX );
        }
        else if ( filepath.find( ".fragment.glsl" ) != std::string::npos )
        {
            shaderCreated = glCreateShader( GL_FRAGMENT_SHADER );
            glShaderSource( shaderCreated, 1, &shaderCode, NULL );
            glCompileShader( shaderCreated );
            CheckCompileErrors( shaderCreated, ShaderType::FRAGMENT );
        }
        else
        {
            EPH_CORE_WARN( "Attempted to compile shader '{0}', but could not due to not being a .glsl vertex or fragment shader.", filepath.c_str() );
        }

        return shaderCreated;
    }

    /**
     * Sets a property of the Shader to a boolean.
     */
    void Shader::SetBool( const char * name, bool value )
    {
        auto it = uniform_cache.find( name );
        if ( it != uniform_cache.end() )
        {
            glUniform1i( ( *it ).second, value );
        }
        else
        {
            int loc = glGetUniformLocation( m_ID, name );
            if ( loc != -1 )
            {
                uniform_cache[name] = loc;
                glUniform1i( loc, value );
            }
            else
            {
                EPH_CORE_WARN( "Variable {0} not found in {1} shader", name, m_Identifier.c_str() );
            }
        }
    }

    /**
     * Sets a property of the Shader to a Vec2.
     */
    void Shader::SetVec2( const char * name, const float2 & vector )
    {
        auto it = uniform_cache.find( name );
        if ( it != uniform_cache.end() )
        {
            glUniform2fv( ( *it ).second, 1, vector.ptr() );
        }
        else
        {
            int loc = glGetUniformLocation( m_ID, name );
            if ( loc != -1 )
            {
                uniform_cache[name] = loc;
                glUniform3fv( loc, 1, vector.ptr() );
            }
            else
            {
                EPH_CORE_WARN( "Variable {0} not found in {1} shader", name, m_Identifier.c_str() );
            }
        }
    }

    /**
     * Sets a property of the Shader to a Vec3.
     */
    void Shader::SetVec3( const char * name, const float3 & vector )
    {
        auto it = uniform_cache.find( name );
        if ( it != uniform_cache.end() )
        {
            glUniform3fv( ( *it ).second, 1, vector.ptr() );
        }
        else
        {
            int loc = glGetUniformLocation( m_ID, name );
            if ( loc != -1 )
            {
                uniform_cache[name] = loc;
                glUniform3fv( loc, 1, vector.ptr() );
            }
            else
            {
                EPH_CORE_WARN( "Variable {0} not found in {1} shader", name, m_Identifier.c_str() );
            }
        }
    }

    /**
     * Sets the Shader's 4x4 matrix.
     */
    void Shader::SetMat4( const char * name, const float4x4 & matrix )
    {
        auto it = uniform_cache.find( name );
        if ( it != uniform_cache.end() )
        {
            glUniformMatrix4fv( ( *it ).second, 1, GL_TRUE, matrix.ptr() );
        }
        else
        {
            int loc = glGetUniformLocation( m_ID, name );
            if ( loc != -1 )
            {
                uniform_cache[name] = loc;
                glUniformMatrix4fv( loc, 1, GL_TRUE, matrix.ptr() );
            }
            else
            {
                EPH_CORE_WARN( "Variable '{0}' not found in '{1}' shader", name, m_Identifier.c_str() );
            }
        }
    }

    /**
     * Set the Shader's identifier (name).
     */
    void Shader::SetName( const char * name )
    {
        m_Identifier.assign( name );
    }

    /**
     * Returns the ID of the shader.
     */
    unsigned int Shader::GetID() const
    {
        return m_ID;
    }

    /**
     * Returns the shader's identifier (name).
     */
    std::string Shader::GetIdentifier() const
    {
        return m_Identifier;
    }

    /**
     * Checks for any errors during shader compilation.
     */
    void Shader::CheckCompileErrors( unsigned int shader, ShaderType type )
    {
        int         success = 0;
        static char infoLog[1024];

        if ( type == ShaderType::PROGRAM )
        {
            glGetProgramiv( shader, GL_LINK_STATUS, &success );
            if ( !success )
            {
                glGetProgramInfoLog( shader, 1024, NULL, infoLog );
                EPH_CORE_ERROR( "Failed to link a shader program: '{0}'", infoLog );
            }
        }
        else
        {
            glGetShaderiv( shader, GL_COMPILE_STATUS, &success );
            if ( !success )
            {
                glGetShaderInfoLog( shader, 1024, NULL, infoLog );
                if ( type == ShaderType::VERTEX )
                {
                    EPH_CORE_ERROR( "Failed to compile a vertex shader: '{0}'", infoLog );
                }
                else
                {
                    EPH_CORE_ERROR( "Failed to compile a fragment shader: '{0}'", infoLog );
                }
            }
        }
    }
}
