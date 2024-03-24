#pragma once

#include "nanoglimpse/Core/Defs.h"

NG_API void OpenGLErrorClear();
NG_API void OpenGLErrorCheck(const char *errCall, const char *file, uint32_t line);

#ifdef NG_DEBUG
    #define GLEC(_glCall) OpenGLErrorClear(); _glCall; OpenGLErrorCheck(#_glCall, __FILE__, __LINE__)
#else
    #define GLEC(_glCall) _glCall
#endif