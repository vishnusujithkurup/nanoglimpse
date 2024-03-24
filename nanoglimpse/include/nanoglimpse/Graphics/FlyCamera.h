#pragma once

#include <glm/glm.hpp>

#include "nanoglimpse/Graphics/Camera.h"

namespace ng::Graphics {
    class NG_API FlyCamera : public Camera {
    public:
        FlyCamera(
            float FOV = 45.f,
            float aspectRatio = 1.f,
            float nearPlane = 0.1f,
            float farPlane = 100.f,
            const glm::vec3& eye = glm::vec3(0.f),
            const glm::vec3& cameraUp = glm::vec3(0.f, 1.f, 0.f),
            float yaw = -90.f,
            float pitch = 0.f
        );

        const glm::vec3& GetPosition() const { return m_Eye; }
        const glm::vec3& GetFrontDirection() const { return m_Front; }
        const glm::vec3& GetRightDirection() const { return m_Right; }

        void SetEyeAt(const glm::vec3 &eye);
        void UpdateProjection(float FOV, float aspectRatio, float nearPlane = 1.f, float farPlane = 100.f);
        void Recalculate(float yaw, float pitch);

        ~FlyCamera();
    
    private:
        glm::vec3 m_Front, m_WorldUp, m_Right, m_Up;

        void RecalculateMatrices();
    };
}