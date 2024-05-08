#pragma once

#ifndef EPH_CORE_IMGUI_H
#    define EPH_CORE_IMGUI_H

#    include <Core/Ephemeral.h>

struct GLFWwindow;

namespace Ephemeral
{
    namespace Imgui
    {
        void Initialize( GLFWwindow * m_Window );
        void NewFrame();
        void RenderFrame();
        void Shutdown();

        void SetDarkThemeColors();
    };
}

#endif
