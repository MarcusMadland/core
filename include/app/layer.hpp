

#pragma once

#include "app/event.hpp"

namespace core 
{
	class Layer
	{
	public:
		explicit Layer(const char* name = "Layer");
		virtual ~Layer() = default;
		
		Layer(const Layer&) = default;
		Layer(Layer&&) = default;
		
		Layer& operator=(const Layer&) = default;
		Layer& operator=(Layer&&) = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(const float& dt) {}
		virtual void onPostUpdate(const float& dt) {}
		virtual void onImGuiRender() {}
		virtual void onEvent(Event& event) {}

		[[nodiscard]] const char* getName() const { return layerName; }

	protected:
		const char* layerName;
	};

	class LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		LayerStack(const LayerStack&) = default;
		LayerStack(LayerStack&&) = default;

		LayerStack& operator=(const LayerStack&) = default;
		LayerStack& operator=(LayerStack&&) = default;

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);
		void popLayer(Layer* layer);
		void popOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers.begin(); }
		std::vector<Layer*>::iterator end() { return layers.end(); }

	private:
		std::vector<Layer*> layers;
		uint32_t layerInsertIndex;
	};

	class ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		ImGuiLayer(const ImGuiLayer&) = default;
		ImGuiLayer(ImGuiLayer&&) = default;

		ImGuiLayer& operator=(const ImGuiLayer&) = default;
		ImGuiLayer& operator=(ImGuiLayer&&) = default;

		void onAttach() override;
		void onDetach() override;
		void onUpdate(const float& dt) override;
		void onImGuiRender() override;

		static void begin();
		static void end();
	};
}