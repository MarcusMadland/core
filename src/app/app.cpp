

#include "crpch.hpp"

#include <GLFW/glfw3.h> // for glfw getTime

#include "app/app.hpp"
#include "renderer/renderer.hpp"
#include "debug/logger.hpp"

namespace core
{
	#define BIND_EVENT_FN(x) std::bind(&App::x, \
		this, std::placeholders::_1)
	App* App::instance = nullptr;

	App::App(const AppParams& params)
		: isRunning(true)
		, isMinimized(false)
		, lastFrameTime(0.0f)
		, deltaTime(0.0f)
	{
		Logger::logInfo("Initializing Application...");

		if (!instance)
		{
			// Initialize core
			
		}

		instance = this;

		// Window
		window = new Window(params.name, params.width, params.height);
		window->setEventCallback(BIND_EVENT_FN(onEvent));

		// Initialize renderer
		Logger::logInfo("Initializing Renderer...");
		Renderer::init();

		// Layers
		#ifdef _DEBUG
		{
			imguiLayer = new ImGuiLayer();
			pushOverlay(imguiLayer);
		}
		#endif
	}

	void App::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
	}

	void App::pushOverlay(Layer* layer)
	{
		layerStack.pushOverlay(layer);
	}

	void App::run()
	{
		Logger::logInfo("Running Application...");

		while (isRunning)
		{
			const auto time = static_cast<float>(glfwGetTime()); // @todo Is this cross-platform friendly?
			deltaTime = time - lastFrameTime;
			lastFrameTime = time;

			if (!isMinimized)
			{
				for (Layer* layer : layerStack)
					layer->onUpdate(deltaTime);


				#ifdef _DEBUG
				{
					core::ImGuiLayer::begin();

					for (Layer* layer : layerStack)
						layer->onImGuiRender();

					core::ImGuiLayer::end();
				}
				#endif
			}

			window->onUpdate();
		}
	}

	void App::shutdown()
	{
		if (isRunning)
		{
			isRunning = false;
		}
		delete window;
	}

	void App::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(onWindowResize));

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	bool App::onWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}

	bool App::onWindowResize(const WindowResizeEvent& e)
	{
		isMinimized = (e.getWidth() == 0 || e.getHeight() == 0);
		return false;
	}
}