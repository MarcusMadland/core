

#include "crpch.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <examples/imgui_impl_bgfx.h>
#include <examples/imgui_impl_glfw.h>
#include <bgfx/bgfx.h>

#include "app/layer.hpp"
#include "app/app.hpp"

namespace Core
{
	Layer::Layer(const char* name)
		: layerName(name)
	{
	}

	LayerStack::LayerStack()
		: layerInsertIndex(0)
	{}

	LayerStack::~LayerStack()
	{
		for (const auto& layer : layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		const auto it = std::find(layers.begin(),
			layers.begin() + layerInsertIndex, layer);

		if (it != layers.begin() + layerInsertIndex)
		{
			layer->OnDetach();
			layers.erase(it);
			layerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		const auto it = std::find(layers.begin() +
			layerInsertIndex, layers.end(), overlay);

		if (it != layers.end())
		{
			overlay->OnDetach();
			layers.erase(it);
		}
	}

	static GLFWwindow* gWindow = NULL;    // Main window

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Flags
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Font
		// io.FontDefault = io.Fonts->AddFontFromFileTTF("", 12.0f)...

		// Style
		ImGui::StyleColorsClassic();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;

			style.Colors[ImGuiCol_WindowBg].w = 1.0f;

			// Standard style here..
		}

		// Get GLFW window for imgui initialzation
		App& app = App::Instance();
		auto* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOther(window, true);
		ImGui_Implbgfx_Init(255);
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_Implbgfx_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate(const float& dt)
	{
	}

	void ImGuiLayer::OnImGuiRender()
	{

	}

	void ImGuiLayer::Begin()
	{
		ImGui_Implbgfx_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::Instance();
		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()),
			static_cast<float>(app.GetWindow().GetHeight()));

		ImGui::Render();

		ImGui_Implbgfx_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}
