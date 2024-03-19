#pragma once

#include <cstdint>

#include "nanoglimpse/Core/Defs.h"

namespace ng::Graphics {
    class NG_API VertexBuffer {
    public:
        VertexBuffer(float *data, uint32_t size);

        void Bind() const;
        void Unbind() const;

        ~VertexBuffer();
    private:
        uint32_t m_ID;
    };
}