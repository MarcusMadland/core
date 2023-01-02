

#include "crpch.hpp"

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

#include <bx/bx.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <GLFW/glfw3.h>
#if BX_PLATFORM_LINUX
#define GLFW_EXPOSE_NATIVE_X11
#elif BX_PLATFORM_WINDOWS
#define GLFW_EXPOSE_NATIVE_WIN32
#elif BX_PLATFORM_OSX
#define GLFW_EXPOSE_NATIVE_COCOA
#endif
#include <GLFW/glfw3native.h>

#include "3rd-party/impl_bgfx/bgfx_callback.hpp"
#include "app/window.hpp"
#include "app/event.hpp"
#include "debug/logger.hpp"


namespace core
{
	Window::Window(const char* name, uint32_t width, uint32_t height)
		: window(nullptr), bgfxCallback(nullptr)
	{
		windowInfo.title = name;
		windowInfo.width = width;
		windowInfo.height = height;
		windowInfo.resetFlags = BGFX_RESET_VSYNC | BGFX_RESET_MSAA_X16;

		Logger::logInfo(std::string("Creating window with name: " + std::string(name) + ", (Width: %u, Height: %u)").c_str(), width, height);

		// Init GLFW
		if (!glfwInit())
		{
			Logger::logCritical("Failed to initialize GLFW");
			return;
		}
			
		// Create GLFW Window
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(
			static_cast<int>(windowInfo.width),
			static_cast<int>(windowInfo.height), 
			windowInfo.title, 
			nullptr, 
			nullptr);
		if (!window)
		{
			Logger::logCritical("Failed to initialize Window");
			return;
		}

		// Init Graphics
		bgfx::renderFrame(); // Call bgfx::renderFrame before bgfx::init to signal to bgfx not to create a render thread.
		bgfx::Init init;
#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD
		init.platformData.ndt = glfwGetX11Display();
		init.platformData.nwh = (void*)(uintptr_t)glfwGetX11Window(window);
#elif BX_PLATFORM_OSX
		init.platformData.nwh = glfwGetCocoaWindow(window);
#elif BX_PLATFORM_WINDOWS
		init.platformData.nwh = glfwGetWin32Window(window);
#endif
		int w, h;
		glfwGetWindowSize(window, &w, &h);

		init.resolution.width = (uint32_t)w;
		init.resolution.height = (uint32_t)h;
		init.resolution.reset = windowInfo.resetFlags;
		bgfxCallback = new BgfxCallback(); // @todo ...
		init.callback = bgfxCallback;
		if (!bgfx::init(init))
		{
			Logger::logCritical("Failed to initialize BGFX");
			return;
		}

		// Set event callbacks
		glfwSetWindowUserPointer(window, &windowInfo);

		glfwSetWindowSizeCallback(window, [](GLFWwindow* window_,
			const  int width_, const int height_)
			{
				WindowInfo& inf =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(window_));
				inf.width = width_;
				inf.height = height_;

				bgfx::reset((uint32_t)width_, (uint32_t)height_, inf.resetFlags);
				bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

				WindowResizeEvent event(width_, height_);
				inf.eventCallback(event);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window_)
			{
				const WindowInfo& data =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(window_));

				WindowCloseEvent event;
				data.eventCallback(event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* currWindow, const int key,
			int scancode, const int action, int mods)
			{
				const WindowInfo& data =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(currWindow));

				switch (action)
				{
					default:
					{
						break;
					}
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.eventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.eventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(window, [](GLFWwindow* currWindow, const uint32_t keycode)
			{
				const WindowInfo& data =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(currWindow));

				KeyTypedEvent event(static_cast<int>(keycode));
				data.eventCallback(event);
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* currWindow, const int button,
			const int action, int mods)
			{
				const WindowInfo& data =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(currWindow));

				switch (action)
				{
					default:
					{
						break;
					}
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.eventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* currWindow,
			const double xOffset, const double yOffset)
			{
				const WindowInfo& data =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(currWindow));

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* currWindow,
			const double xPos, const double yPos)
			{
				const WindowInfo& data =
					*static_cast<WindowInfo*>(glfwGetWindowUserPointer(currWindow));

				MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
				data.eventCallback(event);
			});
	}

	Window::~Window()
	{
		bgfx::shutdown();

		glfwDestroyWindow(window);

		if (bgfxCallback) { delete bgfxCallback; }
		if (window) { delete window; }
	}

	void Window::onUpdate()
	{
		glfwPollEvents();

		// Swap buffers
		bgfx::frame();

		// Set debug text
		#ifdef _DEBUG
			bgfx::setDebug(BGFX_DEBUG_TEXT);
			
			bgfx::dbgTextClear(0, false);
		#elif NDEBUG
			bgfx::setDebug(BGFX_DEBUG_NONE);
		#endif
	}

	void Window::setEventCallback(const std::function<void(Event&)>& callback)
	{
		windowInfo.eventCallback = callback;
	}

	GLFWwindow* Window::getNativeWindow()
	{
		return window;
	}
}
