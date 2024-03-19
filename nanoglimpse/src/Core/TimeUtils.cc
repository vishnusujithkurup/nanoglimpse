#include <GLFW/glfw3.h>

#include "nanoglimpse/Core/TimeUtils.h"

namespace ng::Core::TimeUtils {
    float Now() {
        return float(glfwGetTime());
    }
}