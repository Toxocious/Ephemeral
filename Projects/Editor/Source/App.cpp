#include <Core/Window.hpp>

#if defined _WIN32
#    include <Windows.h>
#endif

#include <gl/GL.h>

int main()
{
    using namespace Ephemeral::Core;
    Window window { 1366, 768, "Ephemeral Editor" };
    window.Run();

    return 0;
}
