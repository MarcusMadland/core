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

#include "primitive/mesh.hpp"
#include "debug/logger.hpp"

namespace Core
{
	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices)
		: vertices(vertices), indices(indices)
	{
		// Vertex Layout following MeshVertex struct
		bgfx::VertexLayout layout;
		layout.begin()
			.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float)
			.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
			.end();

		// Shape 
		bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(bgfx::makeRef(Mesh::vertices.data(), Mesh::vertices.size() * sizeof(MeshVertex)), layout);
		bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(bgfx::makeRef(Mesh::indices.data(), Mesh::indices.size() * sizeof(uint16_t)));
		vao = VertexArray::Create(cubeVbh, cubeIbh);
	}

	Ref<Mesh> Mesh::Create(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices)
	{
		return MakeRef<Mesh>(vertices, indices);
	}
}