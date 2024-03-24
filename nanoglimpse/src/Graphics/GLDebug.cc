#include <string>
#include <glad/glad.h>

#include "nanoglimpse/Core/Log.h"
#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Graphics/GLDebug.h"

static inline const char* GetErrorString(uint32_t err) {
    switch (err) {
        case 0x0500: return "GL_INVALID_ENUM";
        case 0x0501: return "GL_INVALID_VALUE";
        case 0x0502: return "GL_INVALID_OPERATION";
        case 0x0503: return "GL_STACK_OVERFLOW";
        case 0x0504: return "GL_STACK_UNDERFLOW";
        case 0x0505: return "GL_OUT_OF_MEMORY";
        case 0x0506: return "GL_INVALID_FRAMEBUFFER_OPERATION";
        case 0x0507: return "GL_CONTEXT_LOST";
        case 0x8031: return "GL_TABLE_TOO_LARGE";
        default: return "UNKNOWN_ERROR_CODE";
    }
}

void OpenGLErrorClear() {
    while (glGetError() != GL_NO_ERROR);
}

void OpenGLErrorCheck(const char *errCall, const char *file, uint32_t line) {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        NG_INTERNAL_ERROR("[OpenGL ERROR : 0x{0:04X}] '{1}' raised by '{2}' in file '{3}' at line {4}", 
            err, GetErrorString(err), errCall, file, line);
        NG_INTERNAL_ASSERT(false, "OpenGL Error raised!");
    }
}
