#pragma once

#ifndef EPH_CORE_RENDERER_H
#    define EPH_CORE_RENDERER_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

#    include <Renderer/Viewport.h>

#    include <map>

namespace Ephemeral
{
    class Renderer : public Module
    {
    public:
        Renderer( bool start_enabled = true );
        ~Renderer();

    public:
        bool Initialize() override;

        UpdateStatus PreUpdate() override;
        UpdateStatus PostUpdate() override;

        bool Start() override;
        bool CleanUp() override;

        Viewport * CreateViewport( const char * name );
        Viewport * GetViewport( const char * name );

        // EphShader * GetShader( const char * name );

    private:
        // void LoadShaders();

    public:
        int smaa = 4;

    private:
        std::map<std::string, Viewport *> m_Viewports;

        std::map<std::string, unsigned int> m_Shaders;
        // std::map<std::string, EphShader *>   m_Programs;
    };
}

#endif
