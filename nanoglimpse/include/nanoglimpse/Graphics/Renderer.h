#pragma once

#include <glm/glm.hpp>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Graphics/Camera.h"
#include "nanoglimpse/Graphics/Shader.h"
#include "nanoglimpse/Graphics/VertexArray.h"

namespace ng::Graphics {
    class NG_API Renderer {
    public:
        static void Init();

        static void SetClearColor(float r, float g, float b, float a);
        static void UpdateViewport(int x, int y, uint32_t width, uint32_t height);
        static void SetDepthTestsEnabled(bool enabled);
        static void Clear();
        
        static void Begin(const Camera &cam);
        static void Push(const Shader &shader, const VertexArray &va, uint32_t vertexCount, const glm::mat4 &transform = glm::mat4(1.f));
        static void End();
    
    private:
        static uint32_t s_ClearMask;
        static glm::mat4 s_ViewProjectionMatrix;
    };
}