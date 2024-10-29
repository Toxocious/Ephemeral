#pragma once

#ifndef EPH_CORE_SHADER_H
#    define EPH_CORE_SHADER_H

#    include <Core/Ephemeral.h>

#    include <Util/Math/Integer.h>

#    include <MathGeoLib/Math/float2.h>
#    include <MathGeoLib/Math/float4x4.h>

#    include <unordered_map>

class IntegerUtil;

namespace Ephemeral
{
    class Shader
    {
    private:
        friend class Renderer;

        enum class ShaderType
        {
            PROGRAM,
            VERTEX,
            FRAGMENT
        };

    public:
        Shader();
        ~Shader();

        void         Use();
        unsigned int GetID() const;

        void Link( unsigned int vertex, unsigned int fragment );

        std::string GetIdentifier() const;

        void SetBool( const char * name, bool value );

        void SetFloat( const char * name, float value );

        void SetInt( const char * name, int value );
        // void SetInt2( const char * name, const IntegerUtil & value );

        void SetVec2( const char * name, const float2 & vector );
        void SetVec3( const char * name, const float3 & vector );

        void SetMat4( const char * name, const float4x4 & matrix );

    protected:
        void SetName( const char * nname );

    protected:
        unsigned int m_ID;

        std::string m_Identifier;

    private:
        static unsigned int Compile( const std::string & filepath );
        static void         CheckCompileErrors( unsigned int shader, ShaderType type );

    private:
        std::unordered_map<std::string, int> uniform_cache;
    };
}

#endif
