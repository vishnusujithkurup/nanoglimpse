#pragma once

#include <cstdint>

namespace ng::Core::MouseButton {
    using MouseCode = uint32_t;

    enum : MouseCode {
        B1     = 0,
        B2     = 1,
        B3     = 2,
        B4     = 3,
        B5     = 4,
        B6     = 5,
        B7     = 6,
        B8     = 7,
        Last   = B8,
        Left   = B1,
        Right  = B2,
        Middle = B3
    };
}