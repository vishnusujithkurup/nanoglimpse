#pragma once

#include <vector>

#include "nanoglimpse/Core/Defs.h"
#include "nanoglimpse/Core/Layer.h"

namespace ng::Core {
    class NG_API LayerStack {
    public:
        using LayerVec = std::vector<Layer*>;

        void PushLayer(Layer *layer);
        void PopLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void PopOverlay(Layer *layer);

        LayerVec::iterator begin() { return m_LayerStack.begin(); }
        LayerVec::iterator end() { return m_LayerStack.end(); }
        LayerVec::const_iterator begin() const { return m_LayerStack.begin(); }
        LayerVec::const_iterator end() const { return m_LayerStack.end(); }

        LayerVec::reverse_iterator rbegin() { return m_LayerStack.rbegin(); }
        LayerVec::reverse_iterator rend() { return m_LayerStack.rend(); }
        LayerVec::const_reverse_iterator rbegin() const { return m_LayerStack.rbegin(); }
        LayerVec::const_reverse_iterator rend() const { return m_LayerStack.rend(); }

        ~LayerStack();

    private:
        LayerVec m_LayerStack;
        unsigned int m_LayerEnd;
    };
}