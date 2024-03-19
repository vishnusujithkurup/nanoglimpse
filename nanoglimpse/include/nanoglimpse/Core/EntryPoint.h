#pragma once

#include "nanoglimpse/Core/Application.h"
#include "nanoglimpse/Core/Log.h"
#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Core/Input.h"

int main(int argc, char **argv) {
    ng::Core::Log::Init();

    ng::Core::Application *app = ng::Core::CreateApplication();

    ng::Core::Input::ListenTo(app->GetWindow()->GetNativeWindow());

    app->Run();

    delete app;

    return 0;
}