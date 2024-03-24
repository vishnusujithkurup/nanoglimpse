#include <limits>

#include <GLFW/glfw3.h>

#include "nanoglimpse/Core/Input.h"
#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Core/Application.h"

namespace ng::Core {
    bool Input::isKeyPressed(Key::KeyCode k) {
        NG_INTERNAL_ASSERT(Application::GetApplication().GetWindow(), "Window is nullptr!");
        NG_INTERNAL_ASSERT(Application::GetApplication().GetWindow()->GetNativeWindow(), "GLFWwindow* is nullptr!");
        return glfwGetKey(Application::GetApplication().GetWindow()->GetNativeWindow(), k) == GLFW_PRESS;
    }

    bool Input::isMouseButtonPressed(MouseButton::MouseCode k) {
        NG_INTERNAL_ASSERT(Application::GetApplication().GetWindow(), "Window is nullptr!");
        NG_INTERNAL_ASSERT(Application::GetApplication().GetWindow()->GetNativeWindow(), "GLFWwindow* is nullptr!");
        return glfwGetMouseButton(Application::GetApplication().GetWindow()->GetNativeWindow(), k) == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition() {
        NG_INTERNAL_ASSERT(Application::GetApplication().GetWindow(), "Window is nullptr!");
        NG_INTERNAL_ASSERT(Application::GetApplication().GetWindow()->GetNativeWindow(), "GLFWwindow* is nullptr!");
        double xpos, ypos;
        glfwGetCursorPos(Application::GetApplication().GetWindow()->GetNativeWindow(), &xpos, &ypos);
        return {xpos, ypos};
    }
}