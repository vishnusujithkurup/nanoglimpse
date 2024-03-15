#pragma once

#include "nanoglimpse/Events/Event.h"

namespace ng::Events {
    class NG_API WindowResizedEvent : public Event {
    public:
        WindowResizedEvent(int width, int height) : m_Width(width), m_Height(height) {
            Type = EventType::WindowResized;
        }

        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
    
    private:
        int m_Width, m_Height;
    };

    class NG_API WindowClosedEvent : public Event {
    public:
        WindowClosedEvent() { 
            Type = EventType::WindowClosed;
        }
    };
}