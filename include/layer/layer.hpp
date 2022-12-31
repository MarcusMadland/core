

#pragma once

#include "event/event.hpp"

namespace Core 
{
	class Layer
	{
	public:
		explicit Layer(const char* name = "Layer");
		virtual ~Layer() = default;
		
		Layer(const Layer&) = default;
		Layer(Layer&&) = default;
		
		Layer& operator=(const Layer&) = default;
		Layer& operator=(Layer&&) = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(const float& dt) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		[[nodiscard]] const char* GetName() const { return layerName; }

	protected:
		const char* layerName;
	};
}