#include <glad/glad.h>

#include "nanoglimpse/Graphics/VertexArray.h"

namespace ng::Graphics {

    static GLenum GetOpenGLType(BufferElementType Type) {
        switch (Type) {
            case BufferElementType::Float: return GL_FLOAT;
            case BufferElementType::Int: return GL_INT;
            case BufferElementType::Bool: return GL_BOOL;
            default: return 0;
        }
    }

    VertexArray::VertexArray() {
        glGenVertexArrays(1, &m_ID);
    }

    void VertexArray::Bind() const {
        glBindVertexArray(m_ID);
    }

    void VertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::AttachBuffer(const VertexBuffer &vb, const BufferLayout &layout) {
        glBindVertexArray(m_ID);
        vb.Bind();
        uint32_t offset = 0, id = 0;
        for (const auto &ele : layout) {
            glVertexAttribPointer(id, ele.Count, GetOpenGLType(ele.Type), ele.Normalized, layout.GetStride(), (const void*)offset);
            glEnableVertexAttribArray(id);
            ++id;
        }
        glBindVertexArray(0);
    }

    VertexArray::~VertexArray() {
        glDeleteVertexArrays(1, &m_ID);
    }
    
}