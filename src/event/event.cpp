

#include "crpch.hpp"

#include "event/event.hpp"

namespace Core
{
	EventDispatcher::EventDispatcher(Event& event)
		: event(event)
	{}
}