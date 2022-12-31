

#pragma once

#include "window.hpp"
#include "event/event.hpp"
#include "event/app_event.hpp"
#include "layer/layer_stack.hpp"
#include "layer/layers/imgui_layer.hpp"

namespace Core 
{
	class App
	{
	public:
		explicit App(const char* name = "Project", 
			uint32_t width = 1280, uint32_t height = 720);
		virtual ~App() = default;

		App(const App&) = delete;
		App(App&&) = delete;
		
		App& operator=(const App&) = delete;
		App& operator=(App&&) = delete;

		
		void Run();

		
		void Shutdown();

		
		void OnEvent(Event& e);

		
		void PushLayer(Layer* layer);

		
		void PushOverlay(Layer* layer);

		
		static App& Instance() { return *instance; }

		
		[[nodiscard]] Window& GetWindow() const { return *window; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(const WindowResizeEvent& e);

	private:
		Window* window; // @todo Raw pointer? why?
		bool isRunning;
		bool isMinimized;
		
		LayerStack layerStack;
		ImGuiLayer* imguiLayer; // @todo Raw pointer? why?

		float lastFrameTime;
		float deltaTime;

		static App* instance;
	};
}