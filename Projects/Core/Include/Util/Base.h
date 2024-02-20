#pragma once

#include <Util/PlatformDetection.h>

#include <memory>

#ifdef EPH_DEBUG
#    if defined( EPH_PLATFORM_WINDOWS )
#        define EPH_DEBUGBREAK() __debugbreak()
#    elif defined( EPH_PLATFORM_LINUX )
#        include <signal.h>
#        define EPH_DEBUGBREAK() raise( SIGTRAP )
#    else
#        error "Platform doesn't support debugbreak yet!"
#    endif
#    ifndef EPH_ENABLE_ASSERTS
#        define EPH_ENABLE_ASSERTS
#    endif
#else
#    define EPH_DEBUGBREAK()
#endif

#define EPH_EXPAND_MACRO( x )    x
#define EPH_STRINGIFY_MACRO( x ) #x

#define BIT( x ) ( 1 << x )

#define EPH_BIND_EVENT_FN( fn ) [this]( auto &&... args ) -> decltype( auto ) { \
    return this->fn( std::forward<decltype( args )>( args )... );               \
}

namespace Ephemeral
{
    template <typename T>
    using Scope = std::unique_ptr<T>;

    template <typename T, typename... Args>
    constexpr Scope<T> CreateScope( Args &&... args )
    {
        return std::make_unique<T>( std::forward<Args>( args )... );
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;

    template <typename T, typename... Args>
    constexpr Ref<T> CreateRef( Args &&... args )
    {
        return std::make_shared<T>( std::forward<Args>( args )... );
    }
}

#include <Util/Assert.h>
#include <Util/Log.h>
