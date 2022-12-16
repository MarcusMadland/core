/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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

		/*
		 * Call this to run the application
		 */
		void Run();

		/*
		 * This should be called on window event so the application and all
		 * its layers can use them
		 *
		 * @param e Event that gets called
		 */
		void OnEvent(Event& e);

		/*
		 * Add an application layer
		 *
		 * @param layer Layer that should be added
		 */
		void PushLayer(Layer* layer);

		/*
		 * Add an application overlay. These layers will be updated last,
		 * after all other layers
		 *
		 * @param layer Layer that should be added as overlay
		 */
		void PushOverlay(Layer* layer);

		/*
		 * Get and returns a reference to self
		 * 
		 * @return Application Reference
		 */
		static App& Instance() { return *instance; }

		/*
		 * Get and returns a reference to the window
		 * 
		 * @return Window Reference
		 */
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