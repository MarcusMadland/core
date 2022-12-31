

#pragma once

#include <vector>

#include "layer.hpp"

namespace Core 
{
	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		LayerStack(const LayerStack&) = default;
		LayerStack(LayerStack&&) = default;
		
		LayerStack& operator=(const LayerStack&) = default;
		LayerStack& operator=(LayerStack&&) = default;

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }

	private:
		std::vector<Layer*> layers;
		uint32_t layerInsertIndex;
	};
}