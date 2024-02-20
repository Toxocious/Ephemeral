#include <Core/Entrypoint.h>

#include "Gui/EditorLayer.h"

#if defined _WIN32
#    include <Windows.h>
#endif

// #include <gl/GL.h>

// int main()
// {
//     // Ephemeral::Window window { 1366, 768, "Ephemeral Editor" };
//     // window.Run();

//     return 0;
// }

namespace Ephemeral
{
    class EphemeralEditor : public Application
    {
    public:
        EphemeralEditor( const ApplicationSpecification & spec )
            : Application( spec )
        {
            PushLayer( new EditorLayer() );
        }
    };

    Application * CreateApplication( ApplicationCommandLineArgs args )
    {
        ApplicationSpecification spec;
        spec.Name            = "Ephemeral Editor";
        spec.CommandLineArgs = args;

        return new EphemeralEditor( spec );
    }

}
