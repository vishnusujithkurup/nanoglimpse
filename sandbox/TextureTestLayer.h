#pragma once

#include <memory>
#include <filesystem>
#include <nanoglimpse/nanoglimpse.h>

#include "Assets.h"

class TextureTestLayer : public ng::Core::Layer {
public:
    void OnInit() override {
        NG_INFO("Layer initialized!");
        using namespace ng::Graphics;
        
        fcc = std::make_shared<FlyCameraController>(45.f, 1.f, 0.1, 100.f, glm::vec3(0.f, 0.f, 3.f));
        
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        std::string vert = R"(
            #version 330 core

            layout (location=0) in vec3 a_Pos;
            layout (location=1) in vec2 a_TexCoord;

            uniform mat4 u_Model;
            uniform mat4 u_ViewProjection;

            out vec2 sh_TexCoord;

            void main() {
                sh_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.f);
            }
        )";

        std::string frag = R"(
            #version 330 core

            in vec2 sh_TexCoord;
            out vec4 color;

            uniform sampler2D tex1;
            uniform sampler2D tex2;

            void main() {
                color = mix(texture(tex1, sh_TexCoord), texture(tex2, sh_TexCoord), 0.2);
            }
        )";

        Renderer::SetDepthTestsEnabled(true);

        shader = std::make_shared<Shader>("Main", vert, frag);
        tex1 = std::make_shared<Texture2D>(std::filesystem::path(ASSETS_DIR) / "textures/learnopengl.com_container.jpg");
        tex2 = std::make_shared<Texture2D>(std::filesystem::path(ASSETS_DIR) / "textures/learnopengl.com_awesomeface.png");

        shader->Activate();
        shader->UploadInt("tex1", 0);
        shader->UploadInt("tex2", 1);

        va = std::make_shared<VertexArray>();
        VertexBuffer vb(vertices, sizeof(vertices));
        BufferLayout layout;
        layout.Push({3, BufferElementType::Float, false});
        layout.Push({2, BufferElementType::Float, false});
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
        
        glm::vec3 cubePositions[] = {
            glm::vec3( 0.0f,  0.0f,  0.0f), 
            glm::vec3( 2.0f,  5.0f, -15.0f), 
            glm::vec3(-1.5f, -2.2f, -2.5f),  
            glm::vec3(-3.8f, -2.0f, -12.3f),  
            glm::vec3( 2.4f, -0.4f, -3.5f),  
            glm::vec3(-1.7f,  3.0f, -7.5f),  
            glm::vec3( 1.3f, -2.0f, -2.5f),  
            glm::vec3( 1.5f,  2.0f, -2.5f), 
            glm::vec3( 1.5f,  0.2f, -1.5f), 
            glm::vec3(-1.3f,  1.0f, -1.5f)  
        };

        tex1->Bind(0);
        tex2->Bind(1);

        Renderer::Begin(fcc->GetCamera());

        for (int i = 0; i < 10; ++i) {
            glm::mat4 model = glm::translate(glm::mat4(1.f), cubePositions[i]);
            if (i && (i%3 == 0)) {
                model = glm::rotate(model, ng::TimeUtils::Now(), glm::vec3(1.0f, 0.3f, 0.5f));
            } else {
                model = glm::rotate(model, glm::radians(20.f*i), glm::vec3(1.0f, 0.3f, 0.5f));
            }
            Renderer::Push(*shader, *va, 36, model);
        }

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
    std::shared_ptr<ng::Graphics::Texture2D> tex1, tex2;
};