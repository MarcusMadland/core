

#include "crpch.hpp"

#include "event/key_event.hpp"

namespace Core
{
 	KeyEvent::KeyEvent(const int code)
 		: keyCode(code)
 	{}

	KeyPressedEvent::KeyPressedEvent(const int code, const int repeatCount)
		: KeyEvent(code), repeatCount(repeatCount)
	{}

	KeyReleasedEvent::KeyReleasedEvent(const int code)
		: KeyEvent(code)
 	{}

	KeyTypedEvent::KeyTypedEvent(const int keycode)
		: KeyEvent(keycode)
	{}
}
