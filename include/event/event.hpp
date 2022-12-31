

#pragma once

#include <functional>

namespace Core
{
	
	enum class EventType
	{
		None,

		WindowClose, 
		WindowResize, 

		KeyPressed,
		KeyReleased,
		KeyTyped,

		MouseMoved,
		MouseScrolled,
		MouseButtonPressed,
		MouseButtonReleased,
	};
	
	
	#define EVENT_CLASS_TYPE(type) \
		static EventType GetStaticType() { return EventType::##type; } \
		virtual EventType GetEventType() const override { return GetStaticType(); } 

	
	class Event
	{
	public:
		Event() = default;
		virtual ~Event() = default;
		
		Event(const Event&) = default;
		Event(Event&&) = default;
		
		Event& operator=(const Event&) = default;
		Event& operator=(Event&&) = default;
		
		
		[[nodiscard]] virtual EventType GetEventType() const = 0;

		
		bool handled = false;
	};

	
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		explicit EventDispatcher(Event& event);

		
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(*static_cast<T*>(&event));
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};
}