#include "nanoglimpse/Core/Application.h"
#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Core/Layer.h"
#include "nanoglimpse/Utils/TimeUtils.h"
#include "nanoglimpse/Events/KeyEvents.h"
#include "nanoglimpse/Events/MouseEvents.h"
#include "nanoglimpse/Events/WindowEvents.h"

#include <glad/glad.h>
#include "nanoglimpse/Graphics/VertexBuffer.h"
#include "nanoglimpse/Graphics/BufferLayout.h"
#include "nanoglimpse/Graphics/VertexArray.h"
#include "nanoglimpse/Graphics/Shader.h"

namespace ng::Core {
    Application::Application() : m_PrevTime(0.f) {
        m_AppWindow = std::make_unique<Window>(WindowProperties{.Width=800, .Height=800, .VSyncEnabled = false, .Title="Test Application"});
        if (m_AppWindow) {
            m_Running = true;
            m_AppWindow->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        }
    }

    void Application::Run() {
        using namespace ng::Graphics;

        float verts[9] = {
            -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.0f, 0.75f, 0.0f
        };

        VertexBuffer vb(verts, sizeof(verts));
        BufferLayout layout;
        layout.Push({3, BufferElementType::Float, false});
        VertexArray va;
        va.AttachBuffer(vb, layout);

        std::string vert = R"(
            #version 330 core

            layout (location = 0) in vec3 a_Pos;

            void main() {
                gl_Position = vec4(a_Pos, 1.0f);
            }
        )";

        std::string frag = R"(
            #version 330 core

            out vec4 color;

            void main() {
                color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";

        Shader shader("Main", vert, frag);
        
        while (m_Running) {
            float timeNow = ng::TimeUtils::Now();
            float dt = timeNow - m_PrevTime;
            m_PrevTime = timeNow;

            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate(dt);
            }

            m_AppWindow->OnUpdate();

            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Activate();
            va.Bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
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

    Application::~Application() {
    }
}