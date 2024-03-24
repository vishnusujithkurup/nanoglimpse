#include <nanoglimpse/nanoglimpse.h>

#include "CubeTestLayer.h"

class TestApp : public ng::Core::Application {
public:
    TestApp() {
        PushLayer(new CubeTestLayer());
    }

    ~TestApp() {
    }
};

ng::Core::Application* ng::Core::CreateApplication() {
    return new TestApp();
}