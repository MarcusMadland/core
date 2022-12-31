

#include "crpch.hpp"

#include "event/mouse_event.hpp"

namespace Core
{
 	MouseMovedEvent::MouseMovedEvent(const float x, const float y)
 		: mouseX(x), mouseY(y)
 	{}

	MouseScrolledEvent::MouseScrolledEvent(const float xOffset, const float yOffset)
		: offsetX(xOffset), offsetY(yOffset)
	{}

	MouseButtonEvent::MouseButtonEvent(const int button)
		: button(button)
	{}

	MouseButtonPressedEvent::MouseButtonPressedEvent(const int button)
		: MouseButtonEvent(button)
	{}
	
	MouseButtonReleasedEvent::MouseButtonReleasedEvent(const int button)
		: MouseButtonEvent(button)
	{}
}
