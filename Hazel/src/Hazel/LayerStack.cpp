#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {
	LayerStack::LayerStack() { }

	LayerStack::~LayerStack()
	{
		// LayerStack为Application所有
		// 应用结束时，删除所有layer
		for (Layer* layer : m_layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layerInsertIndex, layer);
		++m_layerInsertIndex;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
			--m_layerInsertIndex;
		}
		layer->OnDetach();
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			m_layers.erase(it);
		}
		overlay->OnDetach();
	}
}