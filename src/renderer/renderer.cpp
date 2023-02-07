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
#include "renderer/framebuffer.hpp"
#include "debug/logger.hpp"

namespace core
{
	struct RendererData
	{
		ref<ShaderManager> shaderManager;

		std::vector<bgfx::FrameBufferHandle> framebuffers;

		ref<Camera> currCamera;
		uint16_t currPassID;

	};
	static RendererData* data;

	void Renderer::init()
	{
		data = new RendererData();
		data->shaderManager = makeRef<ShaderManager>();

		// Shaders
		data->shaderManager->loadAndAdd(
			"../../shaders/compiled/uber-vert.bin", 
			"../../shaders/compiled/uber-frag.bin");
		data->shaderManager->loadAndAdd(
			"../../shaders/compiled/postprocess-vert.bin",
			"../../shaders/compiled/postprocess-frag.bin");
		
		#ifdef _DEBUG
			data->shaderManager->loadAndAdd(
				"../../shaders/compiled/debugdraw-vert.bin", 
				"../../shaders/compiled/debugdraw-frag.bin");
		#endif
	}

	void Renderer::shutdown()
	{
		delete data;
	}

	bool Renderer::beginPass(const ref<Camera>& camera, const PassParams& params)
	{
		ASSERT(camera, "Camera is null, camera is needed to render");
		data->currCamera = camera;
		data->currPassID = params.id;

		// Set viewport
		bgfx::setViewRect(params.id, 0, 0, params.width, params.height);

		// @todo fix
		bgfx::setViewClear(params.id, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0xe3fcffff, 1.0f, 0);

		// Set framebuffer
		bgfx::setViewFrameBuffer(params.id, params.framebuffer->handle);
		
		// Update camera uniform to shader
		bgfx::setViewTransform(params.id, &camera->getViewMatrix()[0][0],
			&camera->getProjectionMatrix()[0][0]);

		return true;
	}
	void Renderer::endPass()
	{
	
	}

	void Renderer::render(const uint32_t& width, const uint32_t& height)
	{
		
	}

	void Renderer::getFinalRender()
	{
	}

	void Renderer::submitVertexArray(const ref<VertexArray>& vao,
		const ref<Shader>& shader)
	{
		ASSERT(vao, "Vertex Array Buffer is invalid");
		ASSERT(shader, "Shader is invalid");

		// Handle Vertex Array
		bgfx::setVertexBuffer(0, vao->vertexBuffer->handle);
		bgfx::setIndexBuffer(vao->indexBuffer->handle);

		// Submit
		bgfx::submit(data->currPassID, shader->handle);
	}

	void Renderer::submitVertexArray(const ref<VertexArray>& vao,
		const std::string& shaderName)
	{
		ASSERT(vao, "Vertex Array Buffer is invalid");
		ref<Shader> shaderRef = data->shaderManager->get(shaderName);
		ASSERT(shaderRef, "Shader is invalid");

		// Handle Vertex Array
		bgfx::setVertexBuffer(0, vao->vertexBuffer->handle);
		bgfx::setIndexBuffer(vao->indexBuffer->handle);

		// Submit
		bgfx::submit(data->currPassID, shaderRef->handle);
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