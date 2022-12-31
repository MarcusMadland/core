

#pragma once

#include "event.hpp"

namespace Core
{
	
	class MouseMovedEvent final : public Event
	{
	public:
		MouseMovedEvent(const float x, const float y);

		[[nodiscard]] float GetX() const { return mouseX; }
		[[nodiscard]] float GetY() const { return mouseY; }

		EVENT_CLASS_TYPE(MouseMoved)
		
	private:
		float mouseX, mouseY;
	};

	
	class MouseScrolledEvent final : public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset);

		[[nodiscard]] float GetXOffset() const { return offsetX; }
		[[nodiscard]] float GetYOffset() const { return offsetY; }

		EVENT_CLASS_TYPE(MouseScrolled)
		
	private:
		float offsetX, offsetY;
	};

	
	class MouseButtonEvent : public Event
	{
	public:
		explicit MouseButtonEvent(const int button);
		
		[[nodiscard]] int GetMouseButton() const { return button; }
	
	private:
		int button;
	};

	
	class MouseButtonPressedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonPressedEvent(const int button);

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	
	class MouseButtonReleasedEvent final : public MouseButtonEvent
	{
	public:
		explicit MouseButtonReleasedEvent(const int button);

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}