#include <glm/gtc/matrix_transform.hpp>

#include "nanoglimpse/Graphics/FlyCamera.h"

namespace ng::Graphics {

    FlyCamera::FlyCamera(
        float FOV,
        float aspectRatio,
        float nearPlane,
        float farPlane,
        const glm::vec3& eye,
        const glm::vec3& worldUp,
        float yaw,
        float pitch
    ) : m_Front(glm::vec3(0.f, 0.f, -1.f)), m_WorldUp(worldUp) {
        m_Eye = eye;
        m_ProjectionMatrix = glm::perspective(FOV, aspectRatio, nearPlane, farPlane);
        Recalculate(yaw, pitch);
    }

    void FlyCamera::SetEyeAt(const glm::vec3 &eye) {
        m_Eye = eye;
    }

    void FlyCamera::UpdateProjection(float FOV, float aspectRatio, float nearPlane, float farPlane) {
        m_ProjectionMatrix = glm::perspective(FOV, aspectRatio, nearPlane, farPlane);
        RecalculateMatrices();
    }

    void FlyCamera::Recalculate(float yaw, float pitch) {
        m_Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_Front.y = sin(glm::radians(pitch));
        m_Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_Front = glm::normalize(m_Front);
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
        RecalculateMatrices();
    }

    void FlyCamera::RecalculateMatrices() {
        m_ViewMatrix = glm::lookAt(m_Eye, m_Eye + m_Front, m_Up);
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    FlyCamera::~FlyCamera() {
    }
}