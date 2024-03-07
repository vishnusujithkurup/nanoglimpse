#pragma once

#include "nanoglimpse/Core/Defs.h"

namespace ng::Core {
    class NG_API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    private:
    };

    extern Application* CreateApplication();
}