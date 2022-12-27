#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "graphics/renderer.hpp"
#include "math.hpp"
#include "debug/logger.hpp"

namespace Core
{
	struct RendererData
	{
		Ref<ShaderManager> shaderManager;
		Ref<Camera> camera;

		std::vector<Ref<Mesh>> batchMeshesSeperated;
		std::vector<Transform> batchMeshesSeperatedTransform;
	};
	static RendererData* data;

	void Renderer::Init()
	{
		data = new RendererData();
		data->shaderManager = std::make_shared<ShaderManager>();

		// Shaders
		data->shaderManager->LoadAndAdd(
			"../shaders/compiled/uber-vert.bin", 
			"../shaders/compiled/uber-frag.bin");
		data->shaderManager->LoadAndAdd(
			"../shaders/compiled/simple-vert.bin", 
			"../shaders/compiled/simple-frag.bin");
		
		#ifdef _DEBUG
			data->shaderManager->LoadAndAdd(
				"../shaders/compiled/debugdraw-vert.bin", 
				"../shaders/compiled/debugdraw-frag.bin");
		#endif
	}

	void Renderer::Shutdown()
	{
		delete data;
	}

	bool Renderer::Begin(Ref<Camera> camera)
	{
		data->camera = camera;

		return true;
	}
	void Renderer::End()
	{
		if (data->batchMeshesSeperated.size() > 0)
		{
			for (uint32_t i = 0; i < data->batchMeshesSeperated.size(); i++)
			{
				Logger::LogInfo("Batched Mesh");
			}

			data->batchMeshesSeperated.clear();
			data->batchMeshesSeperatedTransform.clear();
		}
	}

	void Renderer::SubmitVertexArray(Ref<VertexArray> vao, Ref<Shader> shader)
	{
		// If camera is null, meaning we either passed null at begin or never called begin
		// We set it to 0 if no camera is availanble. This only happens in debug draw
		bgfx::ViewId viewID = 0; 
		if (data->camera)
		{
			viewID = data->camera->GetViewID();
		}

		// Handle Vertex Array
		bgfx::setVertexBuffer(0, vao->vbh);
		bgfx::setIndexBuffer(vao->ibh);

		// Submit
		bgfx::submit(viewID, shader->handle);
	}

	void Renderer::SubmitVertexArrayTransform(Ref<VertexArray> vao, Ref<Shader> shader, Transform transform)
	{
		// Handle Transform
		bgfx::setTransform(&Math::ComposeMatrix(transform)[0][0]);

		// Submit
		SubmitVertexArray(vao, shader);
	}

	void Renderer::SubmitMesh(Ref<Mesh> mesh, Transform transform)
	{
		// Handle Transform
		bgfx::setTransform(&(Math::ComposeMatrix(transform) * Math::ComposeMatrix(mesh->GetTransform()))[0][0]);

		// Material
		mesh->GetMaterial()->UpdateUniforms();

		// Submit
		SubmitVertexArray(mesh->GetVertexArray(), mesh->GetMaterial()->GetShader());
	}

	void Renderer::SubmitMeshBatched(Ref<Mesh> mesh, Transform transform)
	{
		data->batchMeshesSeperated.push_back(mesh);
		data->batchMeshesSeperatedTransform.push_back(transform);
	}

	Ref<ShaderManager> Renderer::GetShaderManager()
	{
		return data->shaderManager;
	}
}