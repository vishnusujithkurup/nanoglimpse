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

    class NG_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(double xoffset, double yoffset) : m_OffsetX(xoffset), m_OffsetY(yoffset) {
            Type = EventType::MouseScrolled;
        }

        double GetOffsetX() const { return m_OffsetX; }
        double GetOffsetY() const { return m_OffsetY; }

    private:
        double m_OffsetX, m_OffsetY;
    };

    class NG_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(double xpos, double ypos) : m_X(xpos), m_Y(ypos) {
            Type = EventType::MouseMoved;
        }

        double GetX() const { return m_X; }
        double GetY() const { return m_Y; }

    private:
        double m_X, m_Y;
    }; 
}