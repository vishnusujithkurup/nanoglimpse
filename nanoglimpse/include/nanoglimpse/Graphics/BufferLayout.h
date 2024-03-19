#pragma once

#include <cstdint>
#include <vector>

#include "nanoglimpse/Core/Defs.h"

namespace ng::Graphics {

    enum class NG_API BufferElementType {
        Unknown,
        Float,
        Int,
        Bool
    };

    static uint32_t GetTypeSize(BufferElementType type) {
        switch(type) {
            case BufferElementType::Float: return sizeof(float);
            case BufferElementType::Int: return sizeof(int);
            case BufferElementType::Bool: return 1;
            default: return 0;
        }
    }

    struct NG_API BufferElement {
        uint32_t Count;
        BufferElementType Type;
        bool Normalized;
    };
    
    class NG_API BufferLayout {
    public:

        void Push(BufferElement ele);

        uint32_t GetStride() const { return m_Stride; }

        std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        std::vector<BufferElement> m_Elements;
        uint32_t m_Stride;
    };

}