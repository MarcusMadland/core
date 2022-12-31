

#include "crpch.hpp"

#include "event/app_event.hpp"

namespace Core
{
	WindowResizeEvent::WindowResizeEvent(const uint32_t width, const uint32_t height)
		: width(width), height(height)
	{}
}
