#include "crpch.hpp"

#include "graphics/renderer.hpp"

namespace Core
{
	struct RendererData
	{
		Ref<ShaderLibrary> shaderLibrary;
	};
	static RendererData* data;

	void Renderer::Init()
	{
		data = new RendererData();
		data->shaderLibrary = std::make_shared<ShaderLibrary>();

		// Shaders
		data->shaderLibrary->LoadAndAdd("../shaders/compiled/simple-vert.bin", "../shaders/compiled/simple-frag.bin");
		
		#ifdef _DEBUG
			data->shaderLibrary->LoadAndAdd("../shaders/compiled/debugdraw-vert.bin", "../shaders/compiled/debugdraw-frag.bin");
		#endif
	}

	void Renderer::Shutdown()
	{
		delete data;
	}

	Ref<ShaderLibrary> Renderer::GetShaderLibrary()
	{
		return data->shaderLibrary;
	}
}