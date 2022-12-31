#pragma once

#include "event.hpp"

namespace Core
{
	
	class KeyEvent : public Event
	{
	public:
		explicit KeyEvent(int code);
		[[nodiscard]] int GetKeyCode() const { return keyCode; }

	private:
		int keyCode;
	};

	
	class KeyPressedEvent final : public KeyEvent
	{
	public:
		KeyPressedEvent(const int code, const int repeatCount);

		
		[[nodiscard]] int GetRepeatCount() const { return repeatCount; }

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int repeatCount;
	};

	
	class KeyReleasedEvent final : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(const int code);

		EVENT_CLASS_TYPE(KeyReleased)
	};
	
	
	class KeyTypedEvent final : public KeyEvent
	{
	public:
		explicit KeyTypedEvent(const int keycode);

		EVENT_CLASS_TYPE(KeyTyped)
	};
}