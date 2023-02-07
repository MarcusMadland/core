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

#include "defines.hpp"
#include "debug/logger.hpp"
#include "renderer/mesh.hpp"
#include "renderer/buffers.hpp"
#include "renderer/vertex.hpp"

namespace core
{
	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices,
			const ref<Material>& material)
		: material(material), vertices(std::move(vertices))
		, indices(std::move(indices))
	{
		ASSERT(this->vertices.size() > 0, "Vertices are empty");
		ASSERT(this->indices.size() > 0, "Indices are empty");
		
		if (!material)
		{
			Logger::logWarn("Created mesh contains no material");
		}
		
		std::vector<BufferElement> layout =
		{
			{ AttribType::Float, 3, Attrib::Position },
			{ AttribType::Float, 3, Attrib::Normal },
			{ AttribType::Float, 3, Attrib::Tangent },
			{ AttribType::Float, 3, Attrib::Bitangent },
			{ AttribType::Float, 2, Attrib::TexCoord0 }
		};
		
		ref<VertexBuffer> vertexBuffer = VertexBuffer::create(layout, Mesh::vertices.data(),
			static_cast<uint32_t>(Mesh::vertices.size()) * sizeof(MeshVertex));
		ASSERT(vertexBuffer, "Invalid VertexBuffer");
			
		ref<IndexBuffer> indexBuffer = IndexBuffer::create(Mesh::indices.data(),
			static_cast<uint32_t>(Mesh::indices.size()) * sizeof(uint16_t));
		ASSERT(indexBuffer, "Invalid IndexBuffer");

		vao = VertexArray::create(vertexBuffer, indexBuffer);
		ASSERT(vao, "Invalid VertexArray");
	}

	ref<Mesh> Mesh::create(const std::vector<MeshVertex>& vertices,
			const std::vector<uint16_t>& indices,
			const ref<Material>& material)
	{
		return makeRef<Mesh>(vertices, indices, material);
	}
	void Mesh::setMaterial(const ref<Material>& material)
	{
		this->material = material;
	}
}