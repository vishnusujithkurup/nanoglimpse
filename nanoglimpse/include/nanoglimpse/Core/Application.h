#pragma once

#include <memory>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Core/Window.h"

namespace ng::Core {
    class NG_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(ng::Events::Event &e);

    private:
        bool m_Running;

        std::unique_ptr<Window> m_AppWindow;

        void OnWindowClose();
    };

    extern Application* CreateApplication();
}