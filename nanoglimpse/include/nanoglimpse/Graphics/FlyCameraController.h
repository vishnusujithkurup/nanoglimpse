#pragma once

#include <utility>

#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Graphics/FlyCamera.h"

namespace ng::Graphics {
    class NG_API FlyCameraController {
    public:
        FlyCameraController(
            float FOV = 45.f,
            float aspectRatio = 1.f,
            float nearPlane = 0.1f,
            float farPlane = 100.f,
            const glm::vec3& eye = glm::vec3(0.f),
            const glm::vec3& cameraUp = glm::vec3(0.f, 1.f, 0.f),
            float yaw = -90.f,
            float pitch = 0.f
        );

        FlyCamera& GetCamera() { return m_Camera; }
        const FlyCamera& GetCamera() const { return m_Camera; }
        
        void OnUpdate(float dt);

    private:
        float m_FOV, m_Pitch, m_Yaw;
        float m_MouseSensitivity, m_MoveSpeed;
        glm::vec2 m_MousePos;
        FlyCamera m_Camera;
    };
}