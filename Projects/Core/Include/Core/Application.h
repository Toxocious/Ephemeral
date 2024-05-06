#pragma once
#ifndef EPH_CORE_APP_H
#    define EPH_CORE_APP_H

#    include <Modules/Window.h>

namespace Ephemeral
{
    class Application
    {
    public:
        Application();
        ~Application();

        bool Initialize( std::string name, std::string version, int height, int width );
        bool Start();
        bool CleanUp();

        bool         PreUpdate();
        UpdateStatus Update();
        bool         PostUpdate();

    public:
        Ephemeral::Window * m_Window = nullptr;

    private:
        std::string m_Name;
        std::string m_Version;
        int         m_Height;
        int         m_Width;

        std::vector<Module *> m_Modules;
    };
}

#endif
