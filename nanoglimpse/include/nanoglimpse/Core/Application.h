#pragma once

#include <memory>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Events/KeyEvents.h"
#include "nanoglimpse/Events/MouseEvents.h"
#include "nanoglimpse/Events/WindowEvents.h"
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

        static const Application& GetApplication() { NG_INTERNAL_ASSERT(s_Instance); return *s_Instance; }

        Window* GetWindow() const { return m_AppWindow.get(); }

    private:
        bool m_Running;
        float m_PrevTime;

        LayerStack m_LayerStack;
        std::unique_ptr<Window> m_AppWindow;

        void PropagateEventToLayers(ng::Events::Event &e);
        void OnWindowClose();
        void OnWindowResize(ng::Events::WindowResizedEvent &e);

        static Application* s_Instance;
    };

    extern Application* CreateApplication();
}