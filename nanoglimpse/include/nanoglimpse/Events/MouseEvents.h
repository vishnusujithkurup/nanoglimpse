#pragma once

#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Core/MouseCodes.h"

namespace ng::Events {
    class NG_API MouseButtonPressedEvent : public Event {
    public:
        MouseButtonPressedEvent(const ng::Core::MouseButton::MouseCode code) : m_Code(code) {
            Type = EventType::MouseButtonPressed;
        }

        ng::Core::MouseButton::MouseCode GetMouseButton() const { return m_Code; }

    private:
        ng::Core::MouseButton::MouseCode m_Code;
    };

    class NG_API MouseButtonReleasedEvent : public Event {
    public:
        MouseButtonReleasedEvent(const ng::Core::MouseButton::MouseCode code) : m_Code(code) {
            Type = EventType::MouseButtonReleased;
        }
        
        ng::Core::MouseButton::MouseCode GetMouseButton() const { return m_Code; }

    private:
        ng::Core::MouseButton::MouseCode m_Code;
    };
}