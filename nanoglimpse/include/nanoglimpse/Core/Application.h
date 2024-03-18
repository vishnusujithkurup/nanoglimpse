#pragma once

#include <memory>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Core/Window.h"
#include "nanoglimpse/Core/LayerStack.h"

namespace ng::Core {
    class NG_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
        void OnEvent(ng::Events::Event &e);

        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);

    private:
        bool m_Running;
        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_AppWindow;

        void PropagateEventToLayers(ng::Events::Event &e);
        void OnWindowClose();
    };

    extern Application* CreateApplication();
}