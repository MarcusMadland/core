

#pragma once

#include "layer/layer.hpp"

namespace Core
{
	class ImGuiLayer final : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() override = default;

		ImGuiLayer(const ImGuiLayer&) = default;
		ImGuiLayer(ImGuiLayer&&) = default;

		ImGuiLayer& operator=(const ImGuiLayer&) = default;
		ImGuiLayer& operator=(ImGuiLayer&&) = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate(const float& dt) override;
		void OnImGuiRender() override;

		static void Begin();
		static void End();
	};
}