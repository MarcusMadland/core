

#pragma once

#include "window.hpp"
#include "app/event.hpp"
#include "app/layer.hpp"

namespace core 
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

		
		void run();

		
		void shutdown();

		
		void onEvent(Event& e);

		
		void pushLayer(Layer* layer);

		
		void pushOverlay(Layer* layer);

		
		static App& getInstance() { return *instance; }

		
		[[nodiscard]] Window& getWindow() const { return *window; }

	private:
		bool onWindowClose(WindowCloseEvent& e);
		bool onWindowResize(const WindowResizeEvent& e);

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