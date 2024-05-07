#include <Core/Ephemeral.h>

#include "Gui/Interface.h"

namespace Ephemeral
{
    EditorInterface::EditorInterface( bool enabled )
        : Module( "EditorInterface", enabled )
    {
    }

    EditorInterface::~EditorInterface()
    {
        CleanUp();
    }

    bool EditorInterface::Initialize()
    {
        EPH_CORE_TRACE( "Initializing Editor Window Interface" );

        return true;
    }

    bool EditorInterface::Start()
    {
        EPH_CORE_TRACE( "Starting Editor Window Interface" );

        return true;
    }

    bool EditorInterface::CleanUp()
    {
        EPH_CORE_TRACE( "Cleaning up Editor Window Interface" );

        return true;
    }

    UpdateStatus EditorInterface::Update()
    {
        ShowDebugOverlay();

        return UpdateStatus::UPDATE_CONTINUE;
    }

    void EditorInterface::ShowDebugOverlay()
    {
#ifdef EPH_DEBUG
        Ephemeral::Imgui::RenderFps();
#endif
    }
}
