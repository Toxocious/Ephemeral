#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/_Module.h>

#include "Gui/Interface.h"

int main()
{
    enum class AppState
    {
        EXIT_ERROR = -1,
        EXIT       = 0,

        CREATION,
        INIT,
        START,
        UPDATE,
        FINISH
    };

    const GLuint WIDTH = 1366, HEIGHT = 768;
    const char * APPLICATION_TITLE   = "Ephemeral Map Editor";
    const char * APPLICATION_VERSION = "v0.1";

    Ephemeral::Application * App = nullptr;

    Ephemeral::Log::Init();
    {
        AppState currentState = AppState::CREATION;

        bool running = true;

        while ( running )
        {
            switch ( currentState )
            {
                case AppState::CREATION:
                    EPH_INFO( "Creating application" );
                    {
                        App          = new Ephemeral::Application();
                        currentState = AppState::INIT;
                    }
                    EPH_INFO( "Application successfully created" );
                    break;

                case AppState::INIT:
                    EPH_INFO( "Initializing application and modules" );
                    {
                        if ( App->Initialize( APPLICATION_TITLE, APPLICATION_VERSION, HEIGHT, WIDTH ) )
                        {
                            currentState = AppState::START;

                            auto editorInterface = new Ephemeral::EditorInterface();
                            App->PushLayer( editorInterface );
                        }
                        else
                        {
                            EPH_ERROR( "Failed to create application. Exiting" );
                            currentState = AppState::EXIT_ERROR;
                            break;
                        }
                    }
                    EPH_INFO( "Application successfully initialized" );
                    break;

                case AppState::START:
                    EPH_INFO( "Starting application modules" );
                    {
                        if ( App->Start() )
                        {
                            currentState = AppState::UPDATE;
                        }
                        else
                        {
                            EPH_ERROR( "Failed to start application modules. Exiting" );
                            currentState = AppState::EXIT_ERROR;
                        }
                    }
                    EPH_INFO( "Application modules successfully started" );

                    break;

                case AppState::UPDATE:
                    switch ( App->Update() )
                    {
                        case Ephemeral::UpdateStatus::UPDATE_STOP:
                            currentState = AppState::FINISH;
                            break;
                        case Ephemeral::UpdateStatus::UPDATE_ERROR:
                            currentState = AppState::EXIT_ERROR;
                            break;
                    }
                    break;

                case AppState::FINISH:
                    EPH_INFO( "Cleaning up application before exiting" );
                    {
                        if ( App->CleanUp() )
                        {
                            currentState = AppState::EXIT;
                        }
                        else
                        {
                            EPH_ERROR( "Failed to clean up the application. Exiting" );
                            currentState = AppState::EXIT_ERROR;
                        }
                    }
                    break;

                case AppState::EXIT:
                    EPH_INFO( "Application has successfully exited" );
                    running = false;
                    break;

                case AppState::EXIT_ERROR:
                    EPH_INFO( "Application has exited with errors" );
                    running = false;
                    break;
            }
        }
    }

    delete App;
    App = nullptr;

    return 0;
}
