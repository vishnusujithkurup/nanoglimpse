#pragma once

#include <cstdint>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Graphics/BufferLayout.h"
#include "nanoglimpse/Graphics/VertexBuffer.h"

namespace ng::Graphics {

    class NG_API VertexArray {
    public:
        VertexArray();

        void Bind() const;
        void Unbind() const;

        void AttachBuffer(const VertexBuffer &vb, const BufferLayout &layout);

        ~VertexArray();
    private:
        uint32_t m_ID;
    };

}
