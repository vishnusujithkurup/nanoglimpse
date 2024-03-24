#pragma once

#include <utility>
#include <glm/glm.hpp>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Core/KeyCodes.h"
#include "nanoglimpse/Core/MouseCodes.h"

typedef struct GLFWwindow GLFWwindow;

namespace ng::Core {
    class NG_API Input {
    public:
        static bool isKeyPressed(Key::KeyCode k);
        static bool isMouseButtonPressed(MouseButton::MouseCode k);
        static glm::vec2 GetMousePosition();
    };
}