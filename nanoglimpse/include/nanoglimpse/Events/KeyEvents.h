#pragma once

#include "nanoglimpse/Events/Event.h"
#include "nanoglimpse/Core/KeyCodes.h"

namespace ng::Events {
    class NG_API KeyPressedEvent : public Event {
    public:
        KeyPressedEvent(const ng::Core::Key::KeyCode code) : m_Code(code) {
            Type = EventType::KeyPressed;
        }

        ng::Core::Key::KeyCode GetKeyCode() const { return m_Code; }

    private:
        ng::Core::Key::KeyCode m_Code;
    };

    class NG_API KeyReleasedEvent : public Event {
    public:
        KeyReleasedEvent(const ng::Core::Key::KeyCode code) : m_Code(code) {
            Type = EventType::KeyReleased;
        }

        ng::Core::Key::KeyCode GetKeyCode() const { return m_Code; }
    
    private:
        ng::Core::Key::KeyCode m_Code;
    };
}