

#include "crpch.hpp"

#include <GLFW/glfw3.h>

#include "app/app.hpp"
#include "graphics/renderer.hpp"
#include "debug/logger.hpp"

namespace Core
{
	#define BIND_EVENT_FN(x) std::bind(&App::x, \
		this, std::placeholders::_1)
	App* App::instance = nullptr;

	App::App(const char* name, uint32_t width, uint32_t height)
		: isRunning(true)
		, isMinimized(false)
		, lastFrameTime(0.0f)
		, deltaTime(0.0f)
	{
		Logger::LogInfo("Initializing Application...");

		if (!instance)
		{
			// Initialize core
			
		}

		instance = this;

		// Window
		window = new Window(name, width, height);
		window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		// Initialize renderer
		Logger::LogInfo("Initializing Renderer...");
		Renderer::Init();

		// Layers
		#ifdef _DEBUG
		{
			imguiLayer = new ImGuiLayer();
			PushOverlay(imguiLayer);
		}
		#endif
	}

	void App::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}

	void App::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}

	void App::Run()
	{
		Logger::LogInfo("Running Application...");

		while (isRunning)
		{
			const auto time = static_cast<float>(glfwGetTime()); 
			deltaTime = time - lastFrameTime;
			lastFrameTime = time;

			if (!isMinimized)
			{
				for (Layer* layer : layerStack)
					layer->OnUpdate(deltaTime);


				#ifdef _DEBUG
				{
					Core::ImGuiLayer::Begin();

					for (Layer* layer : layerStack)
						layer->OnImGuiRender();

					Core::ImGuiLayer::End();
				}
				#endif
			}

			window->OnUpdate();
		}
	}

	void App::Shutdown()
	{
		if (isRunning)
		{
			isRunning = false;
		}
	}

	void App::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	bool App::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning = false;
		return true;
	}

	bool App::OnWindowResize(const WindowResizeEvent& e)
	{
		isMinimized = (e.GetWidth() == 0 || e.GetHeight() == 0);
		return false;
	}
}