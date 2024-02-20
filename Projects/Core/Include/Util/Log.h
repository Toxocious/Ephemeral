#pragma once

#include <Util/Base.h>

// This ignores all warnings raised inside External headers
#pragma warning( push, 0 )
#pragma comment( lib, "spdlog" )
#include <spdlog/spdlog.h>

#include <spdlog/fmt/ostr.h>
#pragma warning( pop )

namespace Ephemeral
{
    class Log
    {
    public:
        static void Init();

        static Ref<spdlog::logger> & GetCoreLogger()
        {
            return s_CoreLogger;
        }

        static Ref<spdlog::logger> & GetEditorLogger()
        {
            return s_EditorLogger;
        }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_EditorLogger;
    };
}

// Core log macros
#define EPH_CORE_TRACE( ... )    ::Ephemeral::Log::GetCoreLogger()->trace( __VA_ARGS__ )
#define EPH_CORE_INFO( ... )     ::Ephemeral::Log::GetCoreLogger()->info( __VA_ARGS__ )
#define EPH_CORE_WARN( ... )     ::Ephemeral::Log::GetCoreLogger()->warn( __VA_ARGS__ )
#define EPH_CORE_ERROR( ... )    ::Ephemeral::Log::GetCoreLogger()->error( __VA_ARGS__ )
#define EPH_CORE_CRITICAL( ... ) ::Ephemeral::Log::GetCoreLogger()->critical( __VA_ARGS__ )

// Editor log macros
#define EPH_TRACE( ... )    ::Ephemeral::Log::GetEditorLogger()->trace( __VA_ARGS__ )
#define EPH_INFO( ... )     ::Ephemeral::Log::GetEditorLogger()->info( __VA_ARGS__ )
#define EPH_WARN( ... )     ::Ephemeral::Log::GetEditorLogger()->warn( __VA_ARGS__ )
#define EPH_ERROR( ... )    ::Ephemeral::Log::GetEditorLogger()->error( __VA_ARGS__ )
#define EPH_CRITICAL( ... ) ::Ephemeral::Log::GetEditorLogger()->critical( __VA_ARGS__ )
