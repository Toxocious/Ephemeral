#pragma once
#ifndef EPH_CORE_MODULE_H
#    define EPH_CORE_MODULE_H

#    include <string>

namespace Ephemeral
{
    enum class UpdateStatus
    {
        UPDATE_CONTINUE,
        UPDATE_STOP,
        UPDATE_ERROR
    };

    class Module
    {
    public:
        Module( const char * name, bool enabled );
        virtual ~Module();

        virtual bool Initialize();
        virtual bool Initialize( int height, int width, const char * title );

        virtual bool Start();
        virtual bool CleanUp();

        virtual UpdateStatus PreUpdate();
        virtual UpdateStatus Update();
        virtual UpdateStatus PostUpdate();

        static std::string UpdateStatusToString( UpdateStatus us );

    public:
        std::string m_Name;

    private:
        bool m_Enabled = true;
    };
}

#endif EPH_CORE_MODULE_H
