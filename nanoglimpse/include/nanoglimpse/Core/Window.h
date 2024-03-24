#pragma once

#include <string>
#include <memory>
#include <functional>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Graphics/Context.h"

typedef struct GLFWwindow GLFWwindow;

namespace ng::Core {
    struct WindowProperties {        
        uint32_t Width = 400;
        uint32_t Height = 400;
        bool VSyncEnabled = true;
        bool Resizable = false;
        bool DisableCursor = true;
        std::string Title = "NG App";
    };

    class NG_API Window {
    public:
        Window(WindowProperties props = WindowProperties());
        virtual ~Window();
        
        void OnUpdate();

        int GetWidth() const { return m_Attribs.Props.Width; }
        int GetHeight() const { return m_Attribs.Props.Height; }
        const std::string& GetTitle() const { return m_Attribs.Props.Title; }

        void SetVSyncEnabled(bool enableVSync);
        bool isVSyncEnabled() const { return m_Attribs.Props.VSyncEnabled; }

        void SetEventCallback(const std::function<void(ng::Events::Event&)> &cbFun);

        GLFWwindow* GetNativeWindow() const { return m_GLFWwindow; }

    private:
        static bool Init();

        GLFWwindow *m_GLFWwindow;
        ng::Graphics::Context m_Context;

        static int s_InstanceCount;
        static bool s_GLFWInit;

        struct WindowAttribs {
            std::function<void(ng::Events::Event&)> EventCB;
            WindowProperties Props;
        };

        WindowAttribs m_Attribs;
    };
}