#pragma once

#ifndef EPH_EDITOR_INTERFACE_H
#    define EPH_EDITOR_INTERFACE_H

#    include <Core/Ephemeral.h>

#    include <Modules/_Module.h>

namespace Ephemeral
{
    class EditorInterface : public Module
    {
    public:
        EditorInterface( bool enabled = true );
        ~EditorInterface();

    public:
        bool Initialize() override;
        bool Start() override;
        bool CleanUp() override;

        // UpdateStatus PreUpdate() override;
        UpdateStatus Update() override;
        // UpdateStatus PostUpdate() override;

    public:
        void ShowMenuBar();
        void ShowDebugOverlay();
        void ShowHudButtons();

        void ShowNewMapModal();

    private:
        bool m_showNewMapPopup = false;
    };
}

#endif
