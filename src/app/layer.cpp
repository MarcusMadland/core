

#include "crpch.hpp"

#include <imgui.h>
#include <GLFW/glfw3.h>
#include <examples/imgui_impl_bgfx.h>
#include <examples/imgui_impl_glfw.h>
#include <bgfx/bgfx.h>

#include "app/layer.hpp"
#include "app/app.hpp"

namespace core
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

	void LayerStack::pushLayer(Layer* layer)
	{
		layers.emplace(layers.begin() + layerInsertIndex, layer);
		layerInsertIndex++;
		layer->onAttach();
	}

	void LayerStack::pushOverlay(Layer* overlay)
	{
		layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::popLayer(Layer* layer)
	{
		const auto it = std::find(layers.begin(),
			layers.begin() + layerInsertIndex, layer);

		if (it != layers.begin() + layerInsertIndex)
		{
			layer->onDetach();
			layers.erase(it);
			layerInsertIndex--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay)
	{
		const auto it = std::find(layers.begin() +
			layerInsertIndex, layers.end(), overlay);

		if (it != layers.end())
		{
			overlay->onDetach();
			layers.erase(it);
		}
	}

	static GLFWwindow* gWindow = NULL;    // Main window

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::onAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// Flags
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Font
		//io.FontDefault = io.Fonts->AddFontFromFileTTF("../../core/assets/fonts/Tahoma.ttf", 16.0f);

		// Style
		ImGui::StyleColorsClassic();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;

			// Imgui style here..
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			//style.Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
			//style.Colors[ImGuiCol_Text] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
			
		}

		// Get GLFW window for imgui initialzation
		App& app = App::getInstance();
		auto* window = static_cast<GLFWwindow*>(app.getWindow().getNativeWindow());

		ImGui_ImplGlfw_InitForOther(window, true);
		ImGui_Implbgfx_Init(255);
	}

	void ImGuiLayer::onDetach()
	{
		ImGui_Implbgfx_Shutdown();
		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();
	}

	void ImGuiLayer::onUpdate(const float& dt)
	{
	}

	void ImGuiLayer::onImGuiRender()
	{

	}

	void ImGuiLayer::begin()
	{
		ImGui_Implbgfx_NewFrame();
		ImGui_ImplGlfw_NewFrame();

		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
	}

	void ImGuiLayer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		App& app = App::getInstance();
		io.DisplaySize = ImVec2(static_cast<float>(app.getWindow().getWidth()),
			static_cast<float>(app.getWindow().getHeight()));

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
