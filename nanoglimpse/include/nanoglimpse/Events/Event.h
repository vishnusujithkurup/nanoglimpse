#pragma once

#include "nanoglimpse/Core/Defs.h"

namespace ng::Events {
    enum class EventType {
        Unknown,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseScrolled,
        WindowResized, WindowClosed
    };

    class NG_API Event {
    public:
        virtual ~Event() = default;
        bool Handled = false;
        EventType Type = EventType::Unknown;
    };
}