#pragma once
#ifndef EPH_CORE_APP_H
#    define EPH_CORE_APP_H

#    include <Modules/_Module.h>

#    include <Modules/ImGuiLayer.h>
#    include <Modules/Renderer.h>
#    include <Modules/Scene.h>
#    include <Modules/SceneCamera.h>
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

        void PushLayer( Module * layer );

        inline const float & GetDeltaTime() const
        {
            return m_Window->GetDeltaTime();
        }

    public:
        Ephemeral::Window *      m_Window      = nullptr;
        Ephemeral::ImGuiLayer *  m_ImGuiLayer  = nullptr;
        Ephemeral::Renderer *    m_Renderer    = nullptr;
        Ephemeral::SceneCamera * m_SceneCamera = nullptr;
        Ephemeral::Scene *       m_Scene       = nullptr;

    private:
        std::string m_Name;
        std::string m_Version;
        int         m_Height;
        int         m_Width;

        std::vector<Module *> m_Modules;
    };

}

extern Ephemeral::Application * App;

#endif
