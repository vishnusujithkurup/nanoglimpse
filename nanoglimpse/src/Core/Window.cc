#include <GLFW/glfw3.h>

#include "nanoglimpse/Core/Window.h"
#include "nanoglimpse/Core/Log.h"

#include "nanoglimpse/Events/KeyEvents.h"
#include "nanoglimpse/Events/MouseEvents.h"
#include "nanoglimpse/Events/WindowEvents.h"

namespace ng::Core {
    int Window::s_InstanceCount = 0;
    bool Window::s_GLFWInit = false;

    Window::Window(WindowProperties props) {
        m_Attribs.Props = props;
        if (!s_GLFWInit) {
            Init();
        }
        m_GLFWwindow = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        if (!m_GLFWwindow) {
            NG_INTERNAL_ERROR("Failed to create window!");
        } else {
            NG_INTERNAL_INFO("Created window with Width={0}, Height={1}, Title=\"{2}\"", props.Width, props.Height, props.Title);
            ++s_InstanceCount;
            m_Context.Init(m_GLFWwindow);

            SetVSyncEnabled(props.VSyncEnabled);

            glfwSetWindowUserPointer(m_GLFWwindow, (WindowAttribs*)&m_Attribs);

            glfwSetKeyCallback(m_GLFWwindow, [](GLFWwindow *window, int key, int scancode, int action, int mods){
                WindowAttribs *attribs = (WindowAttribs*)glfwGetWindowUserPointer(window);
                switch (action) {
                    case GLFW_PRESS: {
                        ng::Events::KeyPressedEvent e(key);
                        attribs->EventCB(e);
                        break;
                    }
                    case GLFW_RELEASE: {
                        ng::Events::KeyReleasedEvent e(key);
                        attribs->EventCB(e);
                        break;
                    }
                    default:
                        break;
                }
            });

            glfwSetMouseButtonCallback(m_GLFWwindow, [](GLFWwindow *window, int button, int action, int mods) {
                WindowAttribs *attribs = (WindowAttribs*)glfwGetWindowUserPointer(window);
                switch (action) {
                    case GLFW_PRESS: {
                        ng::Events::MouseButtonPressedEvent e(button);
                        attribs->EventCB(e);
                        break;
                    }
                    case GLFW_RELEASE: {
                        ng::Events::MouseButtonReleasedEvent e(button);
                        attribs->EventCB(e);
                        break;
                    }
                };
            });

            glfwSetWindowSizeCallback(m_GLFWwindow, [](GLFWwindow *window, int width, int height) {
                WindowAttribs *attribs = (WindowAttribs*)glfwGetWindowUserPointer(window);
                attribs->Props.Width = width;
                attribs->Props.Height = height;
                ng::Events::WindowResizedEvent e(width, height);
                attribs->EventCB(e);
            });

            glfwSetWindowCloseCallback(m_GLFWwindow, [](GLFWwindow *window) {
                WindowAttribs *attribs = (WindowAttribs*)glfwGetWindowUserPointer(window);
                ng::Events::WindowClosedEvent e;
                attribs->EventCB(e);
            });
        }
    }

    bool Window::Init() {
        if (s_GLFWInit) {
            return true;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #if defined(NG_PLATFORM_APPLE)
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        if (glfwInit() == GLFW_FALSE) {
            NG_INTERNAL_CRITICAL("GLFW Initialization failed!");
            return false;
        }
        s_GLFWInit = true;
        return true;
    }

    void Window::OnUpdate() {
        glfwPollEvents();
        m_Context.SwapBuffers();
    }

    void Window::SetVSyncEnabled(bool enableVSync) {
        if (enableVSync) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }
        m_Attribs.Props.VSyncEnabled = enableVSync;
    }

    void Window::SetEventCallback(const std::function<void(ng::Events::Event&)> &cbFun) {
        m_Attribs.EventCB = cbFun;
    }

    Window::~Window() {
        if (m_GLFWwindow) {
            glfwDestroyWindow(m_GLFWwindow);
            --s_InstanceCount;

            if (s_InstanceCount == 0) {
                glfwTerminate();
            }
        }
    }
}