#include <iostream>

#include <nanoglimpse/Core/EntryPoint.h>
#include <nanoglimpse/Core/Application.h>
#include <nanoglimpse/Math/Math.h>

class TestApp : public ng::Core::Application {
public:
    TestApp() {
        glm::mat4 a = glm::mat4(1.f);
    }

    ~TestApp() {
    }
};

ng::Core::Application* ng::Core::CreateApplication() {
    return new TestApp();
}