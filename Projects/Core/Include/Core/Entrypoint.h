#pragma once

#include <Core/Application.h>
#include <Util/Base.h>

extern Ephemeral::Application * Ephemeral::CreateApplication( ApplicationCommandLineArgs args );

int main( int argc, char ** argv )
{
    Ephemeral::Log::Init();

    EPH_PROFILE_BEGIN_SESSION( "Startup", "EphemeralProfile-Startup.json" );
    auto app = Ephemeral::CreateApplication( { argc, argv } );
    EPH_PROFILE_END_SESSION();

    EPH_PROFILE_BEGIN_SESSION( "Runtime", "EphemeralProfile-Runtime.json" );
    app->Run();
    EPH_PROFILE_END_SESSION();

    EPH_PROFILE_BEGIN_SESSION( "Shutdown", "EphemeralProfile-Shutdown.json" );
    delete app;
    EPH_PROFILE_END_SESSION();
}
