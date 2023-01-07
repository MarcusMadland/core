/*
 * Copyright 2022 Marcus Madland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "math.hpp"
#include "defines.hpp"
#include "renderer/renderer.hpp"
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
		data->shaderManager = makeRef<ShaderManager>();

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

	bool Renderer::begin(const ref<Camera>& camera)
	{
		ASSERT(camera, "Camera is null, camera is needed to render");

		return true;
	}
	void Renderer::end()
	{
	
	}

	void Renderer::submitVertexArray(const ref<VertexArray>& vao,
		const ref<Shader>& shader)
	{
		ASSERT(vao, "Vertex Array Buffer is invalid");
		ASSERT(shader, "Shader is invalid");
		
		// If camera is null, meaning we either passed null at begin or never called begin
		// We set it to 0 if no camera is available. This only happens in debug draw
		bgfx::ViewId viewID = 0; 
		if (data->camera)
		{
			viewID = static_cast<uint16_t>(data->camera->getViewID());
		}

		// Handle Vertex Array
		bgfx::setVertexBuffer(0, vao->vbh);
		bgfx::setIndexBuffer(vao->ibh);

		// Submit
		bgfx::submit(viewID, shader->handle);
	}

	void Renderer::submitVertexArrayTransform(const ref<VertexArray>& vao,
		const ref<Shader>& shader, const Transform& transform)
	{
		ASSERT(vao, "Vertex Array Buffer is invalid");
		
		// Handle Transform
		bgfx::setTransform(&math::composeMatrix(transform)[0][0]);

		// Submit
		submitVertexArray(vao, shader);
	}

	void Renderer::submitMesh(const ref<Mesh>& mesh, const Transform& transform)
	{
		ASSERT(mesh, "Mesh is invalid");
		
		// Handle Transform
		bgfx::setTransform(&(math::composeMatrix(transform) *
			math::composeMatrix(mesh->getTransform()))[0][0]);

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

	void Renderer::submitBatch(const ref<Batch>& batch, const Transform& transform)
	{
		ASSERT(batch, "Batch is invalid");
		
		if (batch->getBatchedMeshes().empty())
		{
			batch->flush();
		}

		for (uint32_t i = 0; i < batch->getBatchedMeshes().size(); i++)
		{
			submitMesh(batch->getBatchedMeshes()[i], transform);
		}
	}

	ref<ShaderManager> Renderer::getShaderManager()
	{
		return data->shaderManager;
	}
}