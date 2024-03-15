#pragma once

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Core/Log.h"

#if defined(NG_ENABLE_ASSERTS)
    #define NG_ASSERT_WITH_MSG(type, cond, msg, ...) { \
        NG##type##CRITICAL("Assertion '{0}' failed in {1} at line {2}.\nDescription: {3}", #cond, __FILE__, __LINE__, msg);  \
        NG_DEBUGBREAK(); \
    }

    #define NG_ASSERT_NO_MSG(type, cond, ...) { \
        NG##type##CRITICAL("Assertion '{0}' failed in {1} at line {2}.", #cond, __FILE__, __LINE__);  \
        NG_DEBUGBREAK(); \
    }

    #define NG_GET_ASSERT_CONDITION(cond, ...) cond
    #define NG_GET_ASSERT_MESSAGE(cond, msg, ...) msg
    #define NG_GET_ASSERT_MACRO(_exclude1, _exclude2, NG_MACRO_TYPE, ...) NG_MACRO_TYPE

    #define NG_ASSERT_IMPL(type, ...) { \
        if (!(NG_GET_ASSERT_CONDITION(__VA_ARGS__))) { \
            NG_GET_ASSERT_MACRO(__VA_ARGS__, NG_ASSERT_WITH_MSG, NG_ASSERT_NO_MSG)(type, __VA_ARGS__) \
        } \
    }

    #define NG_ASSERT(...) NG_ASSERT_IMPL(_, __VA_ARGS__)
    #define NG_INTERNAL_ASSERT(...) NG_ASSERT_IMPL(_INTERNAL_, __VA_ARGS__)
#else
    #define NG_ASSERT(...) 
    #define NG_INTERNAL_ASSERT(...) 
#endif