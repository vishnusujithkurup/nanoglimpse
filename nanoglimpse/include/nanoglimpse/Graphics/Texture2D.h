#pragma once

#include <string>
#include "nanoglimpse/Graphics/Texture.h"

namespace ng::Graphics {
    struct NG_API Texture2DProps {
        TextureWrapOption SAxisWrap = TextureWrapOption::Repeat;
        TextureWrapOption TAxisWrap = TextureWrapOption::Repeat;
        TextureFilterOption MagnificationFilter = TextureFilterOption::Nearest;
        TextureFilterOption MinificationFilter = TextureFilterOption::Nearest;
    };

    class NG_API Texture2D : public Texture {
    public:

        Texture2D(const std::string &filename, Texture2DProps props = Texture2DProps());

        void Bind(uint32_t slot = 0) const override;
        void Unbind() const override;

        ~Texture2D();

    protected:
        uint32_t m_ID;
    };
}