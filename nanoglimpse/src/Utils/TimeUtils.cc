#include <GLFW/glfw3.h>

#include "nanoglimpse/Utils/TimeUtils.h"

namespace ng::TimeUtils {
    float Now() {
        return float(glfwGetTime());
    }
}