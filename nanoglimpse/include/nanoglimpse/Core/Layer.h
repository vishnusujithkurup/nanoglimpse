#pragma once

#include "nanoglimpse/Core/Defs.h"

namespace ng::Events { class Event; }

namespace ng::Core {
    class NG_API Layer {
    public:
        Layer() = default;
        virtual ~Layer() = default;
        virtual void OnInit() = 0;
        virtual void OnRemove() = 0;
        virtual void OnUpdate(float dt) = 0;
        virtual void OnEvent(ng::Events::Event &e) = 0;
    };
}