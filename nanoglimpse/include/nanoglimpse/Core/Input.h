#pragma once

#include <utility>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Core/KeyCodes.h"
#include "nanoglimpse/Core/MouseCodes.h"

typedef struct GLFWwindow GLFWwindow;

namespace ng::Core {
    class NG_API Input {
    public:
        static void ListenTo(GLFWwindow *window);
        static bool isKeyPressed(Key::KeyCode k);
        static bool isMouseButtonPressed(MouseButton::MouseCode k);
        static std::pair<double, double> GetMousePosition();
    private:
        static GLFWwindow *s_WindowInstance;
    };
}