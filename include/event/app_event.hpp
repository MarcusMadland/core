

#pragma once

#include <memory>

#include "event.hpp"

namespace Core
{
	
	class WindowResizeEvent final : public Event
	{
	public:
		WindowResizeEvent(const uint32_t width, const uint32_t height);

		[[nodiscard]] uint32_t GetWidth() const { return width; }
		[[nodiscard]] uint32_t GetHeight() const { return height; }

		
		EVENT_CLASS_TYPE(WindowResize)

	private:
		uint32_t width;
		uint32_t height;
	};

	
	class WindowCloseEvent final : public Event
	{
	public:

		
		EVENT_CLASS_TYPE(WindowClose)
	};
}
