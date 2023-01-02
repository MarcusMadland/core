

#pragma once

#include "app/event.hpp"

namespace Core 
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

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const float& dt) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		[[nodiscard]] const char* GetName() const { return layerName; }

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

	class ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		ImGuiLayer(const ImGuiLayer&) = default;
		ImGuiLayer(ImGuiLayer&&) = default;

		ImGuiLayer& operator=(const ImGuiLayer&) = default;
		ImGuiLayer& operator=(ImGuiLayer&&) = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(const float& dt) override;
		void OnImGuiRender() override;

		static void Begin();
		static void End();
	};
}