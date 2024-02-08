#pragma once

#include "Core/KeyCodes.h"
#include "Core/MouseCodes.h"

#include <glm/glm.hpp>

namespace Ephemeral
{
    class Input
    {
    public:
        static glm::vec2 GetMousePosition();
        static float     GetMouseX();
        static float     GetMouseY();
        static bool      IsKeyPressed( KeyCode key );
        static bool      IsMouseButtonPressed( MouseCode button );
    };
}
