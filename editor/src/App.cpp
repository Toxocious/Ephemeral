#include "Constants/Editor.h"

#include "Core/Core.h"
#include "Core/Window.h"

#if defined _WIN32
#    include <Windows.h>
#endif

#include <gl/GL.h>

int main()
{
    // Ephemeral::Core::PrintHelloWorld();

    Ephemeral::Window window {
        Ephemeral::Constants::Editor::WINDOW_WIDTH,
        Ephemeral::Constants::Editor::WINDOW_HEIGHT,
        Ephemeral::Constants::Editor::WINDOW_TITLE
    };

    while ( !window.shouldClose() )
    {
        window.pollEvents();

        // Please note: this is old, OpenGL 1.1 code. It's here for simplicity.
        //glBegin( GL_TRIANGLES );
        //glVertex2f( -0.5f, -0.5f );
        //glVertex2f( 0.5f, -0.5f );
        //glVertex2f( 0, 0.5f );
        //glEnd();

        window.swapBuffers();
    }

    return 0;
}
