#include <nanoglimpse/nanoglimpse.h>

#include "CubeTestLayer.h"
#include "TextureTestLayer.h"
#include "ManualLightingTestLayer.h"
#include "ManualSpotLightTestLayer.h"

class TestApp : public ng::Core::Application {
public:
    TestApp() {
        // PushLayer(new CubeTestLayer());
        // PushLayer(new TextureTestLayer());
        // PushLayer(new ManualLightingTestLayer());
        PushLayer(new ManualSpotLightTestLayer());
    }

    ~TestApp() {
    }
};

ng::Core::Application* ng::Core::CreateApplication() {
    return new TestApp();
}