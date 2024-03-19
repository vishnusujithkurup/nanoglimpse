#include <limits>

#include <GLFW/glfw3.h>

#include "nanoglimpse/Core/Input.h"
#include "nanoglimpse/Core/Assert.h"

namespace ng::Core {
    GLFWwindow* Input::s_WindowInstance = nullptr;

    void Input::ListenTo(GLFWwindow *window) {
        NG_INTERNAL_ASSERT(window != nullptr);
        s_WindowInstance = window;
    }

    bool Input::isKeyPressed(Key::KeyCode k) {
        NG_INTERNAL_ASSERT(s_WindowInstance != nullptr);
        return s_WindowInstance ? glfwGetKey(s_WindowInstance, k) == GLFW_PRESS : false;
    }

    bool Input::isMouseButtonPressed(MouseButton::MouseCode k) {
        NG_INTERNAL_ASSERT(s_WindowInstance != nullptr);
        return s_WindowInstance ? glfwGetMouseButton(s_WindowInstance, k) == GLFW_PRESS : false;
    }

    std::pair<double, double> Input::GetMousePosition() {
        NG_INTERNAL_ASSERT(s_WindowInstance != nullptr);
        if (s_WindowInstance) {
            double xpos, ypos;
            glfwGetCursorPos(s_WindowInstance, &xpos, &ypos);
            return {xpos, ypos};
        } else {
            return std::make_pair(std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN());
        }
    }
}