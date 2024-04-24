#pragma once

#include <memory>
#include <filesystem>
#include <nanoglimpse/nanoglimpse.h>

#include "Assets.h"

class ManualSpotLightTestLayer : public ng::Core::Layer {
public:
    void OnInit() override {
        NG_INFO("Layer initialized!");
        NG_TRACE("message");
        NG_WARN("message");
        NG_ERROR("message");
        NG_CRITICAL("message");
        using namespace ng::Graphics;
        
        fcc = std::make_shared<FlyCameraController>(45.f, 1.f, 0.1, 100.f, glm::vec3(0.f, 0.f, 3.f));
        
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };

        std::string objectVert = R"(
            #version 330 core

            layout (location=0) in vec3 a_Pos;
            layout (location=1) in vec3 a_Normal;
            layout (location=2) in vec2 a_TexCoord;

            uniform mat4 u_Model;
            uniform mat4 u_ViewProjection;

            out vec3 sh_Pos;
            out vec3 sh_Normal;
            out vec2 sh_TexCoord;

            void main() {
                sh_Pos = vec3(u_Model * vec4(a_Pos, 1.f));
                sh_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
                sh_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.f);
            }
        )";

        std::string objectFrag = R"(
            #version 330 core

            struct Material {
                sampler2D diffuse;
                sampler2D specular;
                sampler2D emission;
                float shininess;
            };

            struct Light {
                vec3 position;
                vec3 direction;
                vec3 ambient;
                vec3 diffuse;
                vec3 specular;
                float cutOff;
                float constant;
                float linear;
                float quadratic;
            };

            in vec3 sh_Pos;
            in vec3 sh_Normal;
            in vec2 sh_TexCoord;
            out vec4 color;

            uniform vec3 u_ViewPos;
            uniform Material material;
            uniform Light light;
            uniform int isEmissive;

            void main() {
                vec3 lightDir = normalize(light.position - sh_Pos);
                float theta = dot(lightDir, -normalize(light.direction));

                vec3 tmp = vec3(0.f);
                if (theta > light.cutOff) {
                    vec3 ambient = light.ambient * texture(material.diffuse, sh_TexCoord).rgb;
                    vec3 norm = normalize(sh_Normal);
                    float diff = max(dot(norm, lightDir), 0.f);
                    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, sh_TexCoord).rgb;
                    vec3 viewDir = normalize(u_ViewPos - sh_Pos);
                    vec3 reflectDir = reflect(-lightDir, norm);
                    float spec = pow(max(dot(viewDir, reflectDir), 0.f), material.shininess);
                    vec3 specular = light.specular * spec * texture(material.specular, sh_TexCoord).rgb;
                    float distance = length(light.position - sh_Pos);
                    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  
                    diffuse *= attenuation;
                    specular *= attenuation;
                    vec3 result = ambient + diffuse + specular;
                    tmp = result;
                } else {
                    tmp = light.ambient * texture(material.diffuse, sh_TexCoord).rgb;
                }
                vec3 emis = texture(material.emission, sh_TexCoord).rgb;
                if (isEmissive == 1) {
                    color = vec4(tmp + emis, 1.f);
                } else {
                    color = vec4(tmp, 1.f);
                }
            }
        )";

        Renderer::SetDepthTestsEnabled(true);

        objectShader = std::make_shared<Shader>("Object", objectVert, objectFrag);
        tex1 = std::make_shared<Texture2D>(std::filesystem::path(ASSETS_DIR) / "textures/learnopengl.com_container2.png");
        tex2 = std::make_shared<Texture2D>(std::filesystem::path(ASSETS_DIR) / "textures/learnopengl.com_container2_specular.png");
        tex3 = std::make_shared<Texture2D>(std::filesystem::path(ASSETS_DIR) / "textures/learnopengl.com_container2_emission.png");

        objectShader->Activate();
        objectShader->UploadInt("material.diffuse", 0);
        objectShader->UploadInt("material.specular", 1);
        objectShader->UploadInt("material.emission", 2);

        va = std::make_shared<VertexArray>();
        VertexBuffer vb(vertices, sizeof(vertices));
        BufferLayout layout;
        layout.Push({3, BufferElementType::Float, false});
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
        Renderer::SetClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        Renderer::Clear();

        float radius = 3.5f;
        glm::vec3 lightPos(radius * std::sin(ng::TimeUtils::Now()), 0.f, radius * std::cos(ng::TimeUtils::Now()));
        glm::vec3 lightColor(1.0f, 1.0f, 1.0f);

        tex1->Bind(0);
        tex2->Bind(1);
        tex3->Bind(2);

        objectShader->Activate();
        objectShader->UploadVec3("light.position", fcc->GetCamera().GetPosition());
        objectShader->UploadVec3("light.direction", fcc->GetCamera().GetFrontDirection());
        objectShader->UploadFloat("light.cutOff", glm::cos(glm::radians(12.5)));
        objectShader->UploadVec3("u_ViewPos", fcc->GetCamera().GetPosition());
        objectShader->UploadVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
        objectShader->UploadVec3("light.diffuse", glm::vec3(0.8f, 0.8f, 0.8f));
        objectShader->UploadVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        objectShader->UploadFloat("light.constant", 1.f);
        objectShader->UploadFloat("light.linear", 0.09f);
        objectShader->UploadFloat("light.quadratic", 0.032f);
        objectShader->UploadFloat("material.shininess", 32.0f);

        Renderer::Begin(fcc->GetCamera());

        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                if (i == 0 || j == 0 || i == 4 || j == 4 || (i == 2 && j == 2)) {
                    objectShader->UploadInt("isEmissive", 1);
                } else {
                    objectShader->UploadInt("isEmissive", 0);
                }
                glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3((i-2)*1.5f, (j-2)*1.5f, 0.f));
                if (i == 2 && j == 2) {
                    model = glm::rotate(model, ng::TimeUtils::Now(), glm::vec3(1.0f, 0.3f, 0.5f));
                }
                Renderer::Push(*objectShader, *va, 36, model);
            }
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
    std::shared_ptr<ng::Graphics::Shader> objectShader;
    std::shared_ptr<ng::Graphics::Texture2D> tex1, tex2, tex3;
    std::shared_ptr<ng::Graphics::FlyCameraController> fcc;
};