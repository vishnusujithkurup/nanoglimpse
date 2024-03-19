#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "nanoglimpse/Core/Log.h"
#include "nanoglimpse/Core/Assert.h"

#include "nanoglimpse/Graphics/Context.h"

namespace ng::Graphics {
    void Context::Init(GLFWwindow *window) {
        NG_INTERNAL_ASSERT(window != nullptr);
        m_WindowInstance = window;
        glfwMakeContextCurrent(window);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        NG_INTERNAL_ASSERT(status != 0, "Failed to initialize Glad!");

        NG_INTERNAL_INFO("API: OpenGL");
        NG_INTERNAL_INFO("|--> Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        NG_INTERNAL_INFO("|--> Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        NG_INTERNAL_INFO("|--> Version: {0}", (const char*)glGetString(GL_VERSION));
    }

    void Context::SwapBuffers() {
        glfwSwapBuffers(m_WindowInstance);
    }
}