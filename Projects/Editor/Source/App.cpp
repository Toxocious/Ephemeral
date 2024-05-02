#include <Core/Ephemeral.h>
#include <Util/Window.h>

const GLuint WIDTH = 1366, HEIGHT = 768;
const char * WINDOW_TITLE = "Ephemeral Map Editor";

int main()
{
    Ephemeral::Log::Init();

    Ephemeral::Window window( HEIGHT, WIDTH, WINDOW_TITLE );
    window.Run();

    return 0;
}
