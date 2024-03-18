#include <iostream>

#include <nanoglimpse/Core/EntryPoint.h>
#include <nanoglimpse/Core/Application.h>
#include <nanoglimpse/Math/Math.h>
#include <nanoglimpse/Core/Layer.h>

class TestLayer : public ng::Core::Layer {
    void OnInit() override {
        NG_INFO("Layer initialized!");
    }

    void OnRemove() override {
        NG_INFO("Layer removed!");
    }

    void OnUpdate() override {
    }

    void OnEvent(ng::Events::Event &e) override {
    }
};

class TestApp : public ng::Core::Application {
public:
    TestApp() {
        PushLayer(new TestLayer());
    }

    ~TestApp() {
    }
};

ng::Core::Application* ng::Core::CreateApplication() {
    return new TestApp();
}