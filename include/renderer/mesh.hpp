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

#include "common.hpp"

#include "math/transform.hpp"
#include "vertex.hpp"
#include "buffers.hpp"
#include "material.hpp"

namespace core
{
	class Mesh
	{
	public:
		Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices,
			const ref<Material>& material);
		
		static ref<Mesh> create(const std::vector<MeshVertex>& vertices,
			const std::vector<uint16_t>& indices,
			const ref<Material>& material);
		
		[[nodiscard]] Transform getTransform() const { return transform; }
		[[nodiscard]] ref<Material> getMaterial() const { return material; }
		[[nodiscard]] ref<VertexArray> getVertexArray() const { return vao; }

		[[nodiscard]] std::vector<MeshVertex> getVertices() const { return vertices; }
		[[nodiscard]] std::vector<uint16_t> getIndices() const { return indices; }

	private:
		ref<Material> material;
		Transform transform;

		std::vector<MeshVertex> vertices;
		std::vector<uint16_t> indices;
		
		ref<VertexArray> vao;
	};

	
}