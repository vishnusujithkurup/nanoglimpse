#pragma once

#include "nanoglimpse/Core/Application.h"
#include "nanoglimpse/Core/Log.h"

int main(int argc, char **argv) {
    ng::Core::Log::Init();

    NG_INTERNAL_TRACE("Hello, trace message!");
    NG_INTERNAL_INFO("Hello, info message!");
    NG_INTERNAL_ERROR("Hello, error message!");
    NG_INTERNAL_WARN("Hello, warn message!");
    NG_INTERNAL_CRITICAL("Hello, critical!!!");

    NG_CRITICAL("Client critical!!!");

    ng::Core::Application *app = ng::Core::CreateApplication();

    app->Run();

    delete app;

    return 0;
}