#include <iostream>

#include "nanoglimpse/Core/Application.h"
#include "nanoglimpse/Core/Assert.h"

#include "nanoglimpse/Events/KeyEvents.h"
#include "nanoglimpse/Events/MouseEvents.h"
#include "nanoglimpse/Events/WindowEvents.h"
#include "nanoglimpse/Core/Layer.h"

namespace ng::Core {
    Application::Application() {
        m_AppWindow = std::make_unique<Window>(WindowProperties{.Width=800, .Height=800, .Title="Test Application"});
        if (m_AppWindow) {
            m_Running = true;
            m_AppWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        }
    }

    void Application::Run() {
        while (m_Running) {
            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate();
            }

            m_AppWindow->OnUpdate();
        }
    }

    void Application::OnEvent(ng::Events::Event &e) {
        using ng::Events::EventType;
        switch(e.Type) {
            case EventType::WindowClosed: {
                OnWindowClose();
                break;
            }
            case EventType::WindowResized: {
                ng::Events::WindowResizedEvent wre = static_cast<ng::Events::WindowResizedEvent&>(e);
                NG_INTERNAL_INFO("Window with title=\"{0}\" resized, width={1}, height={2}", m_AppWindow->GetTitle(), wre.GetWidth(), wre.GetHeight());
                break;
            }
            case EventType::Unknown: {
                NG_INTERNAL_ERROR("Unknown event received! Ensure event class specifies type!");
                break;
            }
            default: {
                PropagateEventToLayers(e);
                break;
            }
        };
    }

    void Application::PushLayer(Layer *layer) {
        NG_INTERNAL_ASSERT(layer != nullptr, "Attempting to push nullptr layer!");
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        NG_INTERNAL_ASSERT(layer != nullptr, "Attempting to push nullptr overlay!");
        m_LayerStack.PushOverlay(layer);
    }

    void Application::PropagateEventToLayers(ng::Events::Event &e) {
        for (auto it = m_LayerStack.rbegin(); !e.Handled &&  it != m_LayerStack.rend(); ++it) {
            (*it)->OnEvent(e);
        }
    }

    void Application::OnWindowClose() {
        m_Running = false;
    }

    Application::~Application() {
    }
}