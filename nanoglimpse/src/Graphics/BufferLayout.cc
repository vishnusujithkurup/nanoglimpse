#include "nanoglimpse/Graphics/BufferLayout.h"

namespace ng::Graphics {

    void BufferLayout::Push(BufferElement ele) {
        m_Elements.emplace_back(ele);
        m_Stride += ele.Count * GetTypeSize(ele.Type);
    }

}