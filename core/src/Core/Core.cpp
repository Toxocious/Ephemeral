#include "include.h"

#include "Core.h"

#include <utils/time.h>
#include <utils/timer.h>

namespace Ephemeral
{
    namespace Core
    {
        void PrintHelloWorld()
        {
            Ephemeral::Log::Init();

            Ephemeral::Timer timer;

            // std::cout << "Hello World!\n";
            EPH_CORE_TRACE("Hello, world!");

            for ( auto i = 0; i < 10; i++ )
            {
                EPH_CORE_INFO("Time elapsed: {0}ms", timer.ElapsedMillis());
                // std::cout << "Time elapsed: " << timer.ElapsedMillis() << "ms" << std::endl;
                std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );
            }

            std::cin.get();
        }
    }
}
