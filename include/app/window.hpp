


#pragma once

#include <memory>

#include "app/event.hpp"

struct GLFWwindow;
struct BgfxCallback;

namespace core
{
	class Window
	{
	private:
		struct WindowInfo
		{
			WindowInfo()
				: title("window")
				, width(1280)
				, height(720)
				, resetFlags(0)
			{}

			const char* title;
			uint32_t width;
			uint32_t height;
			uint32_t resetFlags;

			std::function<void(Event&)> eventCallback;
		};

	public:
		Window(const char* name, uint32_t width, uint32_t height);
		~Window();

		void onUpdate();
		void setEventCallback(const std::function<void(Event&)>& callback);

		[[nodiscard]] GLFWwindow* getNativeWindow();

		[[nodiscard]] uint32_t getWidth() const { return windowInfo.width; }
		[[nodiscard]] uint32_t getHeight() const { return windowInfo.height; }
		[[nodiscard]] uint32_t getResetFlags() const { return windowInfo.resetFlags; }

	private:
		WindowInfo windowInfo;

		GLFWwindow* window;
		BgfxCallback* bgfxCallback;
	};
}