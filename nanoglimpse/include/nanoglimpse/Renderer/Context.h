#pragma once

#include "nanoglimpse/Core/Defs.h"

typedef struct GLFWwindow GLFWwindow;

namespace ng::Renderer {
    class NG_API Context {
    public:
        void Init(GLFWwindow *window);
        void SwapBuffers();
    private:
        GLFWwindow *m_WindowInstance;
    };
}