#include <Core/Ephemeral.h>

#include <Core/Application.h>

#include <Modules/_Module.h>

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
        EPH_INFO( "Initializing program" );
        {
            AppState currentState = AppState::CREATION;

            bool running = true;

            while ( running )
            {
                switch ( currentState )
                {
                    case AppState::CREATION:
                        EPH_TRACE( "Creating application." );
                        {
                            App          = new Ephemeral::Application();
                            currentState = AppState::INIT;
                        }
                        break;

                    case AppState::INIT:
                        EPH_TRACE( "Initializing application." );
                        {
                            if ( App->Initialize( APPLICATION_TITLE, APPLICATION_VERSION, HEIGHT, WIDTH ) )
                            {
                                currentState = AppState::START;
                            }
                            else
                            {
                                EPH_ERROR( "Failed to create application. Exiting." );
                                currentState = AppState::EXIT_ERROR;
                            }
                        }
                        break;

                    case AppState::START:
                        EPH_TRACE( "Starting application modules." );
                        {
                            if ( App->Start() )
                            {
                                currentState = AppState::UPDATE;
                            }
                            else
                            {
                                EPH_ERROR( "Failed to start application modules. Exiting." );
                                currentState = AppState::EXIT_ERROR;
                            }
                        }
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
                        EPH_TRACE( "Application Finish" );
                        {
                            if ( App->CleanUp() )
                            {
                                currentState = AppState::EXIT;
                            }
                            else
                            {
                                EPH_ERROR( "Failed to clean up the application. Exiting." );
                                currentState = AppState::EXIT_ERROR;
                            }
                        }
                        break;

                    case AppState::EXIT:
                        EPH_TRACE( "Application has successfully exited." );
                        running = false;
                        break;

                    case AppState::EXIT_ERROR:
                        EPH_TRACE( "Application has exited with errors." );
                        running = false;
                        break;
                }
            }
        }
        EPH_INFO( "Program initialized." );
    }

    // Ephemeral::Window window( HEIGHT, WIDTH, WINDOW_TITLE );
    // window.Run();

    delete App;
    App = nullptr;

    return 0;
}
