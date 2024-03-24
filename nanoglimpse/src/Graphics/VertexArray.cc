#include <glad/glad.h>

#include "nanoglimpse/Graphics/VertexArray.h"
#include "nanoglimpse/Graphics/GLDebug.h"

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
        GLEC(glGenVertexArrays(1, &m_ID));
    }

    void VertexArray::Bind() const {
        GLEC(glBindVertexArray(m_ID));
    }

    void VertexArray::Unbind() const {
        glBindVertexArray(0);
    }

    void VertexArray::AttachBuffer(const VertexBuffer &vb, const BufferLayout &layout) {
        GLEC(glBindVertexArray(m_ID));
        vb.Bind();
        uint32_t offset = 0, id = 0;
        for (const auto &ele : layout) {
            GLEC(glVertexAttribPointer(id, ele.Count, GetOpenGLType(ele.Type), ele.Normalized, layout.GetStride(), (const void*)offset));
            GLEC(glEnableVertexAttribArray(id));
            offset += ele.Count * GetTypeSize(ele.Type);
            ++id;
        }
        glBindVertexArray(0);
    }

    VertexArray::~VertexArray() {
        GLEC(glDeleteVertexArrays(1, &m_ID));
    }
    
}