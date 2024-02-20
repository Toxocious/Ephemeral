#pragma once

#include <Core/Window.h>

#include <Util/Base.h>
#include <Util/Timestep.h>

#include <Rendering/ImGuiLayer.h>
#include <Rendering/LayerStack.h>

#include <Events/AppEvent.h>
#include <Events/Event.h>

int main( int argc, char ** argv );

namespace Ephemeral
{
    struct ApplicationCommandLineArgs
    {
        int     Count = 0;
        char ** Args  = nullptr;

        const char * operator[]( int index ) const
        {
            EPH_CORE_ASSERT( index < Count );
            return Args[index];
        }
    };

    struct ApplicationSpecification
    {
        std::string                Name = "Ephemeral App";
        std::string                WorkingDirectory;
        ApplicationCommandLineArgs CommandLineArgs;
    };

    class Application
    {
    public:
        Application( const ApplicationSpecification & specification );
        virtual ~Application();

        void OnEvent( Event & e );

        void PushLayer( Layer * layer );
        void PushOverlay( Layer * layer );

        Window & GetWindow()
        {
            return *m_Window;
        }

        void Close();

        ImGuiLayer * GetImGuiLayer()
        {
            return m_ImGuiLayer;
        }

        static Application & Get()
        {
            return *s_Instance;
        }

        const ApplicationSpecification & GetSpecification() const
        {
            return m_Specification;
        }

        void SubmitToMainThread( const std::function<void()> & function );

    private:
        void Run();
        bool OnWindowClose( WindowCloseEvent & e );
        bool OnWindowResize( WindowResizeEvent & e );

        void ExecuteMainThreadQueue();

    private:
        ApplicationSpecification m_Specification;
        Scope<Window>            m_Window;
        ImGuiLayer *             m_ImGuiLayer;
        bool                     m_Running   = true;
        bool                     m_Minimized = false;
        LayerStack               m_LayerStack;
        float                    m_LastFrameTime = 0.0f;

        std::vector<std::function<void()>> m_MainThreadQueue;
        std::mutex                         m_MainThreadQueueMutex;

    private:
        static Application * s_Instance;
        friend int ::main( int argc, char ** argv );
    };

    Application * CreateApplication( ApplicationCommandLineArgs args );
}
