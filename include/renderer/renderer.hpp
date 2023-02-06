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

#pragma once

#include "shader.hpp"
#include "buffers.hpp"
#include "batch.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "math/transform.hpp"

/*
 * Forward Declarations
 */
class Framebuffer;

namespace core
{
	struct PassParams
	{
		uint16_t id; // order- 0 call first
		uint64_t states;
		uint32_t width;
		uint32_t height;
		ref<Framebuffer> framebuffer;
	};

	class Renderer
	{
	public:
		static void init();
		static void shutdown();

		static bool beginPass(const ref<Camera>& camera, const PassParams& params);
		static void endPass();
		static void render(const uint32_t& width, const uint32_t& height);
		static void getFinalRender();

		static void submitVertexArray(const ref<VertexArray>& vao,
			const ref<Shader>& shader);
		static void submitVertexArray(const ref<VertexArray>& vao,
			const std::string& shaderName);

		static void submitVertexArrayTransform(const ref<VertexArray>& vao,
			const ref<Shader>& shader, const Transform& transform);
		static void submitMesh(const ref<Mesh>& mesh, const Transform& transform);
		static void submitBatch(const ref<Batch>& batch, 
			const Transform& transform = Transform());

		static ref<ShaderManager> getShaderManager();
	};
}