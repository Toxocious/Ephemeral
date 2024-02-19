#pragma once

#include <Util/Base.h>
#include <Util/Log.h>

#include <filesystem>

#ifdef EPH_ENABLE_ASSERTS
#    define EPH_INTERNAL_ASSERT_IMPL( type, check, msg, ... ) \
        {                                                     \
            if ( !( check ) )                                 \
            {                                                 \
                EPH##type##ERROR( msg, __VA_ARGS__ );         \
                EPH_DEBUGBREAK();                             \
            }                                                 \
        }
#    define EPH_INTERNAL_ASSERT_WITH_MSG( type, check, ... ) EPH_INTERNAL_ASSERT_IMPL( type, check, "Assertion failed: {0}", __VA_ARGS__ )
#    define EPH_INTERNAL_ASSERT_NO_MSG( type, check )        EPH_INTERNAL_ASSERT_IMPL( type, check, "Assertion '{0}' failed at {1}:{2}", EPH_STRINGIFY_MACRO( check ), std::filesystem::path( __FILE__ ).filename().string(), __LINE__ )

#    define EPH_INTERNAL_ASSERT_GET_MACRO_NAME( arg1, arg2, macro, ... ) macro
#    define EPH_INTERNAL_ASSERT_GET_MACRO( ... )                         EPH_EXPAND_MACRO( EPH_INTERNAL_ASSERT_GET_MACRO_NAME( __VA_ARGS__, EPH_INTERNAL_ASSERT_WITH_MSG, EPH_INTERNAL_ASSERT_NO_MSG ) )

// Currently accepts at least the condition, with one additional parameter (the message) being optional
#    define EPH_ASSERT( ... )      EPH_EXPAND_MACRO( EPH_INTERNAL_ASSERT_GET_MACRO( __VA_ARGS__ )( _, __VA_ARGS__ ) )
#    define EPH_CORE_ASSERT( ... ) EPH_EXPAND_MACRO( EPH_INTERNAL_ASSERT_GET_MACRO( __VA_ARGS__ )( _CORE_, __VA_ARGS__ ) )
#else
#    define EPH_ASSERT( ... )
#    define EPH_CORE_ASSERT( ... )
#endif
