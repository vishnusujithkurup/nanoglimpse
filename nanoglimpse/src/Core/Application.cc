#include <iostream>

#include "nanoglimpse/Core/Application.h"
#include "nanoglimpse/Core/Assert.h"

#include "nanoglimpse/Events/KeyEvents.h"
#include "nanoglimpse/Events/MouseEvents.h"
#include "nanoglimpse/Events/WindowEvents.h"

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
            m_AppWindow->OnUpdate();
        }
    }

    void Application::OnEvent(ng::Events::Event &e) {
        using ng::Events::EventType;
        switch(e.Type) {
            case EventType::KeyPressed: {
                ng::Events::KeyPressedEvent kpe = static_cast<ng::Events::KeyPressedEvent&>(e);
                if (kpe.GetKeyCode() == ng::Core::Key::Escape) {
                    OnWindowClose();
                }
                break;
            }
            case EventType::KeyReleased: {
                ng::Events::KeyReleasedEvent kre = static_cast<ng::Events::KeyReleasedEvent&>(e);
                break;
            }
            case EventType::WindowClosed: {
                OnWindowClose();
                break;
            }
            case EventType::WindowResized: {
                ng::Events::WindowResizedEvent wre = static_cast<ng::Events::WindowResizedEvent&>(e);
                NG_INTERNAL_INFO("Window with title=\"{0}\" resized, width={1}, height={2}", m_AppWindow->GetTitle(), wre.GetWidth(), wre.GetHeight());
                break;
            }
            case EventType::MouseButtonPressed: {
                ng::Events::MouseButtonPressedEvent mbpe = static_cast<ng::Events::MouseButtonPressedEvent&>(e);
                break;
            }
            case EventType::MouseButtonReleased: {
                ng::Events::MouseButtonReleasedEvent mbre = static_cast<ng::Events::MouseButtonReleasedEvent&>(e);
                break;
            }
            case EventType::Unknown: {
                NG_INTERNAL_ERROR("Unknown event received! Ensure event class specifies type!");
                break;
            }
        };
    }

    void Application::OnWindowClose() {
        m_Running = false;
    }

    Application::~Application() {
    }
}