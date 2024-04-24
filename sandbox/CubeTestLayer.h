#pragma once

#include <memory>

#include <nanoglimpse/nanoglimpse.h>

class CubeTestLayer : public ng::Core::Layer {
public:
    void OnInit() override {
        NG_INFO("Layer initialized!");

        using namespace ng::Graphics;
        
        fcc = std::make_shared<FlyCameraController>(45.f, 1.f, 0.1, 100.f, glm::vec3(0.f, 0.f, 3.f));
        
        float vertices[] = {
            -0.5f, -0.5f, -0.5f, 1, 0.176, 0.961,
            0.5f, -0.5f, -0.5f,  0.329, 0.078, 0.922,
            0.5f,  0.5f, -0.5f,  0.988, 0.086, 0.271,
            0.5f,  0.5f, -0.5f,  0.988, 0.086, 0.271,
            -0.5f,  0.5f, -0.5f, 0.11, 0.98, 0.557,
            -0.5f, -0.5f, -0.5f, 1, 0.176, 0.961,
            
            -0.5f, -0.5f,  0.5f, 1, 0.984, 0.208,
            0.5f, -0.5f,  0.5f,  0.937, 0.153, 0.969,
            0.5f,  0.5f,  0.5f,  0.584, 0.953, 1,
            0.5f,  0.5f,  0.5f,  0.584, 0.953, 1,
            -0.5f,  0.5f,  0.5f, 1, 0.941, 0.996,
            -0.5f, -0.5f,  0.5f, 1, 0.984, 0.208,
            
            -0.5f,  0.5f,  0.5f, 1, 0.941, 0.996,
            -0.5f,  0.5f, -0.5f, 0.11, 0.98, 0.557,
            -0.5f, -0.5f, -0.5f, 1, 0.176, 0.961,
            -0.5f, -0.5f, -0.5f, 1, 0.176, 0.961,
            -0.5f, -0.5f,  0.5f, 1, 0.984, 0.208,
            -0.5f,  0.5f,  0.5f, 1, 0.941, 0.996,
            
            0.5f,  0.5f,  0.5f,  0.584, 0.953, 1,
            0.5f,  0.5f, -0.5f,  0.988, 0.086, 0.271,
            0.5f, -0.5f, -0.5f,  0.329, 0.078, 0.922,
            0.5f, -0.5f, -0.5f,  0.329, 0.078, 0.922,
            0.5f, -0.5f,  0.5f,  0.937, 0.153, 0.969,
            0.5f,  0.5f,  0.5f,  0.584, 0.953, 1,
            
            -0.5f, -0.5f, -0.5f, 1, 0.176, 0.961,
            0.5f, -0.5f, -0.5f,  0.329, 0.078, 0.922,
            0.5f, -0.5f,  0.5f,  0.937, 0.153, 0.969,
            0.5f, -0.5f,  0.5f,  0.937, 0.153, 0.969,
            -0.5f, -0.5f,  0.5f, 1, 0.984, 0.208,
            -0.5f, -0.5f, -0.5f, 1, 0.176, 0.961,
            
            -0.5f,  0.5f, -0.5f, 0.11, 0.98, 0.557,
            0.5f,  0.5f, -0.5f,  0.988, 0.086, 0.271,
            0.5f,  0.5f,  0.5f,  0.584, 0.953, 1,
            0.5f,  0.5f,  0.5f,  0.584, 0.953, 1,
            -0.5f,  0.5f,  0.5f, 1, 0.941, 0.996,
            -0.5f,  0.5f, -0.5f, 0.11, 0.98, 0.557,
        };

        std::string vert = R"(
            #version 330 core

            layout (location=0) in vec3 a_Pos;
            layout (location=1) in vec3 a_Color;

            uniform mat4 u_Model;
            uniform mat4 u_ViewProjection;

            out vec3 sh_Color;

            void main() {
                sh_Color = a_Color;
                gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.f);
            }
        )";

        std::string frag = R"(
            #version 330 core

            in vec3 sh_Color;
            out vec4 color;

            void main() {
                color = vec4(sh_Color, 1.f);
            }
        )";

        Renderer::SetDepthTestsEnabled(true);

        shader = std::make_shared<Shader>("Main", vert, frag);
        va = std::make_shared<VertexArray>();
        VertexBuffer vb(vertices, sizeof(vertices));
        BufferLayout layout;
        layout.Push({3, BufferElementType::Float, false});
        layout.Push({3, BufferElementType::Float, false});
        va->AttachBuffer(vb, layout);
    }

    void OnRemove() override {
        NG_INFO("Layer removed!");
    }

    void OnUpdate(float dt) override {
        using namespace ng::Graphics;

        fcc->OnUpdate(dt);
        Renderer::SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        Renderer::Clear();

        glm::mat4 model = glm::rotate(glm::mat4(1.f), ng::TimeUtils::Now(), glm::vec3(0.5f, 1.f, 0.f));
        model = glm::scale(model, glm::vec3(glm::sin(ng::TimeUtils::Now())));
        
        Renderer::Begin(fcc->GetCamera());
        Renderer::Push(*shader, *va, 36, model);
        Renderer::End();
    }

    void OnEvent(ng::Events::Event &e) override {
        using namespace ng::Events;
        if (e.Type == EventType::WindowResized) {
            WindowResizedEvent wre = static_cast<WindowResizedEvent&>(e);
            fcc->GetCamera().UpdateProjection(45.f, float(wre.GetWidth()) / float(wre.GetHeight()));
        }
    }

private:
    std::shared_ptr<ng::Graphics::VertexArray> va;
    std::shared_ptr<ng::Graphics::Shader> shader;
    std::shared_ptr<ng::Graphics::FlyCameraController> fcc;
};