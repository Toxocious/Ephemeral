#pragma once

#include <Util/KeyCodes.h>
#include <Util/MouseCodes.h>

#include <glm/vec2.hpp>

namespace Ephemeral
{
    class Input
    {
    public:
        static bool IsKeyPressed( KeyCode key );
        static bool IsMouseButtonPressed( MouseCode button );

        static float GetMouseX();
        static float GetMouseY();

        static glm::vec2 GetMousePosition();
    };
}
