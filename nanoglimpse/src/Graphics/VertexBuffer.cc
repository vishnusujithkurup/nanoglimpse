#include <glad/glad.h>

#include "nanoglimpse/Graphics/VertexBuffer.h"
#include "nanoglimpse/Graphics/GLDebug.h"

namespace ng::Graphics {

    VertexBuffer::VertexBuffer(float *data, uint32_t size) {
        GLEC(glGenBuffers(1, &m_ID));
        GLEC(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
        GLEC(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    void VertexBuffer::Bind() const {
        GLEC(glBindBuffer(GL_ARRAY_BUFFER, m_ID));
    }

    void VertexBuffer::Unbind() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    VertexBuffer::~VertexBuffer() {
        GLEC(glDeleteBuffers(1, &m_ID));
    }

}