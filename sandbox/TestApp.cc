#include <iostream>

#include <nanoglimpse/Core/EntryPoint.h>
#include <nanoglimpse/Core/Application.h>

class TestApp : public ng::Core::Application {
public:
    TestApp() {
    }

    ~TestApp() {
    }
};

ng::Core::Application* ng::Core::CreateApplication() {
    return new TestApp();
}