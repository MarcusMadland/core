

#include "crpch.hpp"

#include "layer/layer_stack.hpp"

namespace Core
{
	LayerStack::LayerStack()
		: layerInsertIndex(0)
	{}
	
	LayerStack::~LayerStack()
	{
		for (const auto& layer : layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto it = std::find(layers.begin(),
			layers.begin() + layerInsertIndex, layer);

		if (it != layers.begin() + layerInsertIndex)
		{
			layer->OnDetach();
			layers.erase(it);
			layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		const auto it = std::find(layers.begin() +
			layerInsertIndex, layers.end(), overlay);

		if (it != layers.end())
		{
			overlay->OnDetach();
			layers.erase(it);
		}
	}
}