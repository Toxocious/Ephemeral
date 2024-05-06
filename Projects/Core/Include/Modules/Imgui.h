#pragma once

#ifndef EPH_CORE_IMGUI_H
#    define EPH_CORE_IMGUI_H

#    include <Core/Ephemeral.h>

struct GLFWwindow;

namespace Ephemeral
{
    namespace Imgui
    {
        // Initialization and frame handling
        void Initialize( GLFWwindow * m_Window );
        void NewFrame();
        void RenderFrame();
        void Shutdown();

        // Misc.
        void RenderFps();
    };
}

#endif
