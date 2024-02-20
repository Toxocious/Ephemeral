#include <Core/Window.h>

#include <Platforms/Windows/WindowsWindow.h>

namespace Ephemeral
{
    Scope<Window> Window::Create( const WindowProps & props )
    {
        return CreateScope<WindowsWindow>( props );
    }
}
