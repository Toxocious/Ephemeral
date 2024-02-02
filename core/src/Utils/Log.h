#pragma once

#include "include.h"

#include "Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning( push, 0 )
#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>
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

        static Ref<spdlog::logger> & GetClientLogger()
        {
            return s_ClientLogger;
        }

    private:
        static Ref<spdlog::logger> s_CoreLogger;
        static Ref<spdlog::logger> s_ClientLogger;
        static Ref<spdlog::logger> s_EditorLogger;
    };
}

template <typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream & operator<<( OStream & os, const glm::vec<L, T, Q> & vector )
{
    return os << glm::to_string( vector );
}

template <typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream & operator<<( OStream & os, const glm::mat<C, R, T, Q> & matrix )
{
    return os << glm::to_string( matrix );
}

template <typename OStream, typename T, glm::qualifier Q>
inline OStream & operator<<( OStream & os, glm::qua<T, Q> quaternion )
{
    return os << glm::to_string( quaternion );
}

// Core log macros
#define EPH_CORE_TRACE( ... )    ::Ephemeral::Log::GetCoreLogger()->trace( __VA_ARGS__ )
#define EPH_CORE_INFO( ... )     ::Ephemeral::Log::GetCoreLogger()->info( __VA_ARGS__ )
#define EPH_CORE_WARN( ... )     ::Ephemeral::Log::GetCoreLogger()->warn( __VA_ARGS__ )
#define EPH_CORE_ERROR( ... )    ::Ephemeral::Log::GetCoreLogger()->error( __VA_ARGS__ )
#define EPH_CORE_CRITICAL( ... ) ::Ephemeral::Log::GetCoreLogger()->critical( __VA_ARGS__ )

// Client log macros
#define EPH_TRACE( ... )    ::Ephemeral::Log::GetClientLogger()->trace( __VA_ARGS__ )
#define EPH_INFO( ... )     ::Ephemeral::Log::GetClientLogger()->info( __VA_ARGS__ )
#define EPH_WARN( ... )     ::Ephemeral::Log::GetClientLogger()->warn( __VA_ARGS__ )
#define EPH_ERROR( ... )    ::Ephemeral::Log::GetClientLogger()->error( __VA_ARGS__ )
#define EPH_CRITICAL( ... ) ::Ephemeral::Log::GetClientLogger()->critical( __VA_ARGS__ )
