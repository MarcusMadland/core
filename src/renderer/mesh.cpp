

#include "crpch.hpp"

#include <bgfx/bgfx.h>

#include "renderer/mesh.hpp"
#include "renderer/buffers.hpp"
#include "renderer/vertex.hpp"

namespace core
{
	Mesh::Mesh(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, ref<Material> material)
		: vertices(vertices), indices(indices), material(material)
	{
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
		bgfx::VertexBufferHandle cubeVbh = bgfx::createVertexBuffer(bgfx::makeRef(Mesh::vertices.data(), Mesh::vertices.size() * sizeof(MeshVertex)), layout);
		bgfx::IndexBufferHandle cubeIbh = bgfx::createIndexBuffer(bgfx::makeRef(Mesh::indices.data(), Mesh::indices.size() * sizeof(uint16_t)));
		vao = VertexArray::create(cubeVbh, cubeIbh);
	}

	ref<Mesh> Mesh::create(std::vector<MeshVertex> vertices, std::vector<uint16_t> indices, ref<Material> material)
	{
		return makeRef<Mesh>(vertices, indices, material);
	}
}