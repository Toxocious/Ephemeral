#pragma once

#include <Util/KeyCodes.h>
#include <Util/MouseCodes.h>

// #include <glm/glm.hpp>

namespace Ephemeral
{
    class Input
    {
    public:
        static bool IsKeyPressed( KeyCode key );
        static bool IsMouseButtonPressed( MouseCode button );

        static float GetMouseX();
        static float GetMouseY();
    };
}
