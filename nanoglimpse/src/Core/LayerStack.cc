#include <algorithm>

#include "nanoglimpse/Core/Assert.h"
#include "nanoglimpse/Core/LayerStack.h"

namespace ng::Core {
    void LayerStack::PushLayer(Layer *layer) {
        NG_INTERNAL_ASSERT(layer != nullptr, "Attempting to push nullptr layer!");
        m_LayerStack.emplace(m_LayerStack.begin() + m_LayerEnd, layer);
    }

    void LayerStack::PopLayer(Layer *layer) {
        NG_INTERNAL_ASSERT(!m_LayerStack.empty(), "Attempting to pop from empty layer stack!");
        if (LayerVec::iterator it = std::find(m_LayerStack.begin(), m_LayerStack.begin() + m_LayerEnd, layer); it != m_LayerStack.begin() + m_LayerEnd) {
            m_LayerStack.erase(it);
        }
    }

    void LayerStack::PushOverlay(Layer *layer) {
        NG_INTERNAL_ASSERT(layer != nullptr, "Attempting to push nullptr overlay!");
        m_LayerStack.emplace_back(layer);
    }

    void LayerStack::PopOverlay(Layer *layer) {
        NG_INTERNAL_ASSERT(m_LayerStack.begin() + m_LayerEnd != m_LayerStack.end(), "Attempting to pop from empty overlay stack!");
        if (LayerVec::iterator it = std::find(m_LayerStack.begin() + m_LayerEnd, m_LayerStack.end(), layer); it != m_LayerStack.end()) {
            m_LayerStack.erase(it);
        }
    }

    LayerStack::~LayerStack() {
        for (Layer *layer : m_LayerStack) {
            if (layer) {
                layer->OnRemove();
            }
        }
    }
}