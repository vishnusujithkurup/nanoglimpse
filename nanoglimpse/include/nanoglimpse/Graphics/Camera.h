#pragma once

#include <glm/glm.hpp>

#include "nanoglimpse/Core/Defs.h"

namespace ng::Graphics {
    class NG_API Camera {
    public:
        virtual ~Camera() = default;

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    protected:
        glm::vec3 m_Eye;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewProjectionMatrix;
    };
}

