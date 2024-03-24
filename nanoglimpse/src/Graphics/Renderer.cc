#include <glad/glad.h>

#include "nanoglimpse/Graphics/Renderer.h"
#include "nanoglimpse/Graphics/GLDebug.h"
#include "nanoglimpse/Core/Log.h"

namespace ng::Graphics {
    uint32_t Renderer::s_ClearMask = 0;
    glm::mat4 Renderer::s_ViewProjectionMatrix = glm::mat4(1.f);

    void Renderer::Init() {
    }

    void Renderer::SetClearColor(float r, float g, float b, float a) {
        GLEC(glClearColor(r, g, b, a));
        s_ClearMask |= GL_COLOR_BUFFER_BIT;
    }

    void Renderer::SetDepthTestsEnabled(bool enabled) {
        if (enabled) {
            GLEC(glEnable(GL_DEPTH_TEST));
            s_ClearMask |= GL_DEPTH_BUFFER_BIT;
        } else if ((s_ClearMask & GL_DEPTH_BUFFER_BIT) == GL_DEPTH_BUFFER_BIT) {
            GLEC(glDisable(GL_DEPTH_TEST));
            s_ClearMask ^= GL_DEPTH_BUFFER_BIT;
        }
    }

    void Renderer::Clear() {
        GLEC(glClear(s_ClearMask));
    }

    void Renderer::UpdateViewport(int x, int y, uint32_t width, uint32_t height) {
        GLEC(glViewport(x, y, width, height));
    }

    void Renderer::Begin(const Camera &cam) {
        s_ViewProjectionMatrix = cam.GetViewProjectionMatrix();
    }

    void Renderer::Push(const Shader &shader, const VertexArray &va, uint32_t vertexCount, const glm::mat4 &transform) {
        shader.Activate();
        shader.UploadMat4("u_Model", transform);
        shader.UploadMat4("u_ViewProjection", s_ViewProjectionMatrix);
        va.Bind();
        GLEC(glDrawArrays(GL_TRIANGLES, 0, vertexCount));
    }

    void Renderer::End() {
    }
}
