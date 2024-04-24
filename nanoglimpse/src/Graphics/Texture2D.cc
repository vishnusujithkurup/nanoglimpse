#include <glad/glad.h>
#include <stb_image.h>

#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Graphics/GLDebug.h"
#include "nanoglimpse/Graphics/Texture2D.h"

namespace ng::Graphics {
    static GLint GetOpenGLWrapOption(TextureWrapOption opt) {
        switch (opt) {
            case TextureWrapOption::Repeat: return GL_REPEAT;
            case TextureWrapOption::MirroredRepeat: return GL_MIRRORED_REPEAT;
            case TextureWrapOption::ClampToEdge: return GL_CLAMP_TO_EDGE;
            case TextureWrapOption::ClampToBorder: return GL_CLAMP_TO_BORDER;
            default: NG_INTERNAL_ASSERT(false, "Unknown texture wrap option!"); return -1;
        }
    }

    static GLint GetOpenGLFilterOption(TextureFilterOption opt) {
        switch (opt) {
            case TextureFilterOption::Nearest: return GL_NEAREST;
            case TextureFilterOption::Linear: return GL_LINEAR;
            case TextureFilterOption::Nearest_MipmapNearest: return GL_NEAREST_MIPMAP_NEAREST;
            case TextureFilterOption::Nearest_MipmapLinear: return GL_NEAREST_MIPMAP_LINEAR;
            case TextureFilterOption::Linear_MipmapNearest: return GL_LINEAR_MIPMAP_NEAREST;
            case TextureFilterOption::Linear_MipmapLinear: return GL_LINEAR_MIPMAP_LINEAR;
            default: NG_INTERNAL_ASSERT(false, "Unknown texture filter option!"); return -1;
        }
    }

    Texture2D::Texture2D(const std::string &filename, Texture2DProps props) {
        GLEC(glGenTextures(1, &m_ID));
        GLEC(glBindTexture(GL_TEXTURE_2D, m_ID));
        GLEC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GetOpenGLWrapOption(props.SAxisWrap)));
        GLEC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GetOpenGLWrapOption(props.SAxisWrap)));
        GLEC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GetOpenGLFilterOption(props.MinificationFilter)));
        GLEC(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GetOpenGLFilterOption(props.MagnificationFilter)));

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc *data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
        GLenum format = 0;
        if (channels == 1) format = GL_RED;
        else if (channels == 3) format = GL_RGB;
        else format = GL_RGBA;
        if (data) {
            GLEC(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
            GLEC(glGenerateMipmap(GL_TEXTURE_2D));
        } else {
            NG_INTERNAL_ERROR("Failed to load texture '{0}'!", filename);
        }
        stbi_image_free(data);
    }

    void Texture2D::Bind(uint32_t slot) const {
        GLEC(glActiveTexture(GL_TEXTURE0 + slot));
        GLEC(glBindTexture(GL_TEXTURE_2D, m_ID));
    }

    void Texture2D::Unbind() const {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    Texture2D::~Texture2D() {
        GLEC(glDeleteTextures(1, &m_ID));
    }
}