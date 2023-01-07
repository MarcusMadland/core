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
		assert(vertices.size() > 0, "Vertices are empty");
		assert(indices.size() > 0, "Indices are empty");
		
		if (!material)
		{
			Logger::logWarn("Created mesh contains no material");
		}
		
		// Vertex Layout following MeshVertex struct
		bgfx::VertexLayout layout;
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord7, 4, bgfx::AttribType::Float)
			.end();

		// Shape 
		const bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(
			bgfx::makeRef(Mesh::vertices.data(),
				static_cast<uint32_t>(Mesh::vertices.size()) *
				sizeof(MeshVertex)), layout);
		const bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(
			bgfx::makeRef(Mesh::indices.data(),
				static_cast<uint32_t>(Mesh::indices.size()) *
				sizeof(uint16_t)));
		vao = VertexArray::create(cubeVbh, cubeIbh);
	}

	ref<Mesh> Mesh::create(const std::vector<MeshVertex>& vertices,
			const std::vector<uint16_t>& indices,
			const ref<Material>& material)
	{
		return makeRef<Mesh>(vertices, indices, material);
	}
}