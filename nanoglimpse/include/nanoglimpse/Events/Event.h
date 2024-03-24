#pragma once

#include "nanoglimpse/Core/Defs.h"

namespace ng::Events {
    enum class NG_API EventType {
        Unknown,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
        WindowResized, WindowClosed
    };

    class NG_API Event {
    public:
        virtual ~Event() = default;
        bool Handled = false;
        EventType Type = EventType::Unknown;
    };
}