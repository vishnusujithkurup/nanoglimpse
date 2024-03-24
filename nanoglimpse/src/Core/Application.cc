#include "nanoglimpse/Core/Application.h"
#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Core/Layer.h"
#include "nanoglimpse/Utils/TimeUtils.h"

#include <glad/glad.h>
#include "nanoglimpse/Graphics/VertexBuffer.h"
#include "nanoglimpse/Graphics/BufferLayout.h"
#include "nanoglimpse/Graphics/VertexArray.h"
#include "nanoglimpse/Graphics/Shader.h"
#include "nanoglimpse/Graphics/Renderer.h"

namespace ng::Core {
    Application* Application::s_Instance = nullptr;

    Application::Application() : m_PrevTime(0.f) {
        NG_INTERNAL_ASSERT(!s_Instance, "Only single application instance allowed!");
        s_Instance = this;

        m_AppWindow = std::make_unique<Window>(WindowProperties{.Width=800, .Height=800, .VSyncEnabled = false, .Title="Test Application"});
        if (m_AppWindow) {
            m_Running = true;
            m_AppWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        }
    }

    

    void Application::Run() {
        using namespace ng::Graphics;
        
        while (m_Running) {
            float timeNow = ng::TimeUtils::Now();
            float dt = timeNow - m_PrevTime;
            m_PrevTime = timeNow;

            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate(dt);
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
                auto wre = static_cast<ng::Events::WindowResizedEvent&>(e);
                OnWindowResize(wre);
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
        layer->OnInit();
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer *layer) {
        NG_INTERNAL_ASSERT(layer != nullptr, "Attempting to push nullptr overlay!");
        layer->OnInit();
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

    void Application::OnWindowResize(ng::Events::WindowResizedEvent &e) {
        ng::Graphics::Renderer::UpdateViewport(0, 0, e.GetWidth(), e.GetHeight());
    }

    Application::~Application() {
    }
}