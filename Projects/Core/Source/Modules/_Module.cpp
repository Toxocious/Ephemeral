#include <Core/Ephemeral.h>

#include <Modules/_Module.h>

#include <string>

namespace Ephemeral
{
    Module::Module( const char * name, bool enabled )
        : m_Name( name ), m_Enabled( enabled )
    {
    }

    Module::~Module()
    {
    }

    bool Module::Initialize()
    {
        return true;
    }

    bool Module::Initialize( int height, int width, const char * title )
    {
        return true;
    }

    bool Module::Start()
    {
        return true;
    }

    UpdateStatus Module::PreUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus Module::Update()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    UpdateStatus Module::PostUpdate()
    {
        return UpdateStatus::UPDATE_CONTINUE;
    }

    bool Module::CleanUp()
    {
        return true;
    }

    std::string Module::UpdateStatusToString( UpdateStatus updateStatus )
    {
        switch ( updateStatus )
        {
            case UpdateStatus::UPDATE_CONTINUE:
                return std::string( "Update Continue" );
            case UpdateStatus::UPDATE_STOP:
                return std::string( "Update Stop" );
            case UpdateStatus::UPDATE_ERROR:
                return std::string( "Update Error" );
        }

        return std::string( "NONE" );
    }
}
