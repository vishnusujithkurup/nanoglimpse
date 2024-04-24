#pragma once

#include <memory>
#include <filesystem>
#include <nanoglimpse/nanoglimpse.h>

#include "Assets.h"

class ManualLightingTestLayer : public ng::Core::Layer {
public:
    void OnInit() override {
        NG_INFO("Layer initialized!");
        using namespace ng::Graphics;
        
        fcc = std::make_shared<FlyCameraController>(45.f, 1.f, 0.1, 100.f, glm::vec3(0.f, 0.f, 3.f));
        
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };

        std::string objectVert = R"(
            #version 330 core

            layout (location=0) in vec3 a_Pos;
            layout (location=1) in vec3 a_Normal;

            uniform mat4 u_Model;
            uniform mat4 u_ViewProjection;

            out vec3 sh_Pos;
            out vec3 sh_Normal;

            void main() {
                sh_Pos = a_Pos;
                sh_Normal = a_Normal;
                gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.f);
            }
        )";

        std::string objectFrag = R"(
            #version 330 core

            in vec3 sh_Pos;
            in vec3 sh_Normal;
            out vec4 color;

            uniform vec3 u_ViewPos;
            uniform vec3 u_LightColor;
            uniform vec3 u_LightPos;
            uniform vec3 u_ObjectColor;

            void main() {
                vec3 ambient = 0.1 * u_LightColor;
                
                vec3 norm = normalize(sh_Normal);
                vec3 lightDir = normalize(u_LightPos - sh_Pos);
                float diff = max(dot(norm, lightDir), 0.0);
                vec3 diffuse = diff * u_LightColor;

                vec3 viewDir = normalize(u_ViewPos - sh_Pos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float coeff = pow(max(dot(reflectDir, viewDir), 0.0), 32);
                vec3 specular = 0.5 * coeff * u_LightColor;

                vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
                color = vec4(result, 1.f);
            }
        )";

        std::string lampVert = R"(
            #version 330 core

            layout (location=0) in vec3 a_Pos;

            uniform mat4 u_Model;
            uniform mat4 u_ViewProjection;

            void main() {
                gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.f);
            }
        )";

        std::string lampFrag = R"(
            #version 330 core

            out vec4 color;

            uniform vec3 u_LightColor;

            void main() {
                color = vec4(u_LightColor, 1.f);
            }
        )";

        Renderer::SetDepthTestsEnabled(true);

        objectShader = std::make_shared<Shader>("Object", objectVert, objectFrag);
        lampShader = std::make_shared<Shader>("Lamp", lampVert, lampFrag);

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
        Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        Renderer::Clear();

        float radius = 3.5f;
        glm::vec3 lightPos(radius * std::sin(ng::TimeUtils::Now()), 0.f, radius * std::cos(ng::TimeUtils::Now()));
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        Renderer::Begin(fcc->GetCamera());

        objectShader->Activate();
        objectShader->UploadVec3("u_ObjectColor", glm::vec3(1.0f, 0.5f, 0.31f));
        objectShader->UploadVec3("u_LightColor", lightColor);
        objectShader->UploadVec3("u_LightPos", lightPos);
        objectShader->UploadVec3("u_ViewPos", fcc->GetCamera().GetPosition());
        Renderer::Push(*objectShader, *va, 36);

        lampShader->Activate();
        lampShader->UploadVec3("u_LightColor", lightColor);
        glm::mat4 model = glm::translate(glm::mat4(1.f), lightPos);
        model = glm::scale(model, glm::vec3(0.2f));
        Renderer::Push(*lampShader, *va, 36, model);

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
    std::shared_ptr<ng::Graphics::Shader> objectShader, lampShader;
    std::shared_ptr<ng::Graphics::FlyCameraController> fcc;
};