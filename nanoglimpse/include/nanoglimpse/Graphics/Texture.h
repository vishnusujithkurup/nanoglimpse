#pragma once

#include <cstdint>
#include "nanoglimpse/Core/Defs.h"

namespace ng::Graphics {
    enum class NG_API TextureWrapOption {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder,
    };

    enum class NG_API TextureFilterOption {
        Nearest,
        Linear,
        Nearest_MipmapNearest,
        Nearest_MipmapLinear,
        Linear_MipmapNearest,
        Linear_MipmapLinear
    };

    class NG_API Texture {
    public:
        virtual ~Texture() = default;

        virtual void Bind(uint32_t slot = 0) const = 0;
        virtual void Unbind() const = 0;
    protected:
        uint32_t m_ID;
    };
}