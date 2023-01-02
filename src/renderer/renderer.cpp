#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "renderer/renderer.hpp"
#include "math.hpp"
#include "debug/logger.hpp"

namespace core
{
	struct RendererData
	{
		ref<ShaderManager> shaderManager;
		ref<Camera> camera;
	};
	static RendererData* data;

	void Renderer::init()
	{
		data = new RendererData();
		data->shaderManager = std::make_shared<ShaderManager>();

		// Shaders
		data->shaderManager->loadAndAdd(
			"../shaders/compiled/uber-vert.bin", 
			"../shaders/compiled/uber-frag.bin");
		data->shaderManager->loadAndAdd(
			"../shaders/compiled/simple-vert.bin", 
			"../shaders/compiled/simple-frag.bin");
		
		#ifdef _DEBUG
			data->shaderManager->loadAndAdd(
				"../shaders/compiled/debugdraw-vert.bin", 
				"../shaders/compiled/debugdraw-frag.bin");
		#endif
	}

	void Renderer::shutdown()
	{
		delete data;
	}

	bool Renderer::begin(ref<Camera> camera)
	{
		data->camera = camera;

		return true;
	}
	void Renderer::end()
	{
	
	}

	void Renderer::submitVertexArray(ref<VertexArray> vao, ref<Shader> shader)
	{
		// If camera is null, meaning we either passed null at begin or never called begin
		// We set it to 0 if no camera is availanble. This only happens in debug draw
		bgfx::ViewId viewID = 0; 
		if (data->camera)
		{
			viewID = data->camera->getViewID();
		}

		// Handle Vertex Array
		bgfx::setVertexBuffer(0, vao->vbh);
		bgfx::setIndexBuffer(vao->ibh);

		// Submit
		bgfx::submit(viewID, shader->handle);
	}

	void Renderer::submitVertexArrayTransform(ref<VertexArray> vao, ref<Shader> shader, Transform transform)
	{
		// Handle Transform
		bgfx::setTransform(&math::composeMatrix(transform)[0][0]);

		// Submit
		submitVertexArray(vao, shader);
	}

	void Renderer::submitMesh(ref<Mesh> mesh, Transform transform)
	{
		// Handle Transform
		bgfx::setTransform(&(math::composeMatrix(transform) * math::composeMatrix(mesh->getTransform()))[0][0]);

		// Only submit mesh if material is valid 
		// @todo Add standard material if not material is submitted
		if (mesh->getMaterial())
		{
			// Material
			mesh->getMaterial()->updateUniforms();

			// Submit
			submitVertexArray(mesh->getVertexArray(), mesh->getMaterial()->getShader());
		}
	}

	void Renderer::submitBatch(ref<Batch> batch)
	{
		if (batch->currBatchedIndices.size() > 0 || batch->currBatchedVertices.size() > 0)
		{
			batch->flush();
		}

		for (uint32_t i = 0; i < batch->getBatchedMeshes().size(); i++)
		{
			submitMesh(batch->getBatchedMeshes()[i], Transform());
		}
	}

	ref<ShaderManager> Renderer::getShaderManager()
	{
		return data->shaderManager;
	}
}