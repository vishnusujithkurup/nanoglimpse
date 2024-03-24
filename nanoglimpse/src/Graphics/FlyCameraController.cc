#include "nanoglimpse/Core/Log.h"
#include "nanoglimpse/Core/Input.h"
#include "nanoglimpse/Events/KeyEvents.h"
#include "nanoglimpse/Events/MouseEvents.h"
#include "nanoglimpse/Graphics/FlyCameraController.h"

namespace ng::Graphics {
    FlyCameraController::FlyCameraController(
        float FOV,
        float aspectRatio,
        float nearPlane,
        float farPlane,
        const glm::vec3& eye,
        const glm::vec3& cameraUp,
        float yaw,
        float pitch
    ) : m_Camera(FOV, aspectRatio, nearPlane, farPlane, eye, cameraUp, yaw, pitch), m_FOV(FOV),
        m_Yaw(yaw), m_Pitch(pitch), m_MouseSensitivity(5.f), m_MoveSpeed(2.f), m_MousePos(ng::Core::Input::GetMousePosition()) {
    }

    void FlyCameraController::OnUpdate(float dt) {
        using namespace ng::Core;
        auto curMousePos = Input::GetMousePosition();
        auto mouseOffset = curMousePos - m_MousePos;
        m_Yaw += mouseOffset.x * m_MouseSensitivity * dt;
        m_Pitch += -mouseOffset.y * m_MouseSensitivity * dt;
        m_MousePos = curMousePos;
        if (m_Pitch > 89.f) m_Pitch = 89.f;
        if (m_Pitch < -89.f) m_Pitch  = -89.f;

        auto curPos = m_Camera.GetPosition();
        if (Input::isKeyPressed(Key::W)) {
            curPos += m_Camera.GetFrontDirection() * m_MoveSpeed * dt;
        } else if (Input::isKeyPressed(Key::S)) {
            curPos -= m_Camera.GetFrontDirection() * m_MoveSpeed * dt;
        } else if (Input::isKeyPressed(Key::D)) {
            curPos += m_Camera.GetRightDirection() * m_MoveSpeed * dt;
        } else if (Input::isKeyPressed(Key::A)) {
            curPos -= m_Camera.GetRightDirection() * m_MoveSpeed * dt;
        }

        m_Camera.SetEyeAt(curPos);
        m_Camera.Recalculate(m_Yaw, m_Pitch);
    }
}